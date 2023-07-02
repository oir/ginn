// Copyright 2022 Bloomberg Finance L.P.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef GINN_NODE_PICK_H
#define GINN_NODE_PICK_H

#include <ginn/node.h>
#include <ginn/node/data.h>
#include <ginn/nonlin.h>
#ifdef GINN_ENABLE_GPU
#include <thrust/gather.h>
#include <thrust/tuple.h>
#endif

namespace ginn {

template <typename Scalar, DeviceKind Kind>
class PickNode : public BaseDataNode<Scalar, Kind> {
 protected:
  NodePtr<Scalar, Kind> in_;
  DataPtr<Int, Kind> index_; // TODO: Make this NodePtr<Int> instead

 public: // Cuda needs this public
#ifdef GINN_ENABLE_GPU
  struct StridedIndex {
    Int stride = 0;

    template <typename Tuple>
    __host__ __device__ auto operator()(Tuple t) {
      auto& count = thrust::get<0>(t);
      auto& index = thrust::get<1>(t);
      return stride * count + index;
    }
  };
#endif

 public:
  using BaseDataNode<Scalar, Kind>::dev;
  using BaseDataNode<Scalar, Kind>::value;
  using BaseDataNode<Scalar, Kind>::grad;

 protected:
  void pick(Tensor<Scalar, Kind>& input) {
    value().resize({1, input.cols()});
    auto& index = index_->value();
    GINN_ASSERT(input.cols() == index.size(),
                "Index size does not match input columns! (" +
                    std::to_string(index.size()) + "≠" +
                    std::to_string(input.cols()));
    if constexpr (Kind == CPU) {
      auto vv = value().v();
      auto ivm = input.m();
      auto iv = index.v();
      for (Size i = 0; i < index.size(); i++) { vv[i] = ivm.col(i)[iv[i]]; }
#ifdef GINN_ENABLE_GPU
    } else if constexpr (Kind == GPU) {
      Int rows = input.rows();
      auto index_begin = thrust::device_ptr<Int>(index.data());
      auto ct_begin = thrust::make_counting_iterator(Int(0));
      auto map_begin = thrust::make_transform_iterator(
          make_zip_iterator(make_tuple(ct_begin, index_begin)),
          StridedIndex{rows});
      thrust::gather(thrust::device,
                     map_begin,
                     map_begin + index.size(),
                     thrust::device_ptr<Raw<Scalar>>(input.data()),
                     thrust::device_ptr<Raw<Scalar>>(value().data()));
#endif
    } else {
      GINN_THROW("Unexpected device!");
    }
  }

  void pick_grad(Tensor<Scalar, Kind>& grad_in, bool negate = false) {
    auto& index = index_->value();
    if (in_->has_grad()) {
      if constexpr (Kind == CPU) {
        auto iv = index.v();
        auto gv = grad().v();
        auto igm = grad_in.m();
        for (Size i = 0; i < index.size(); i++) {
          if (negate) {
            igm.col(i)[iv[i]] -= gv[i];
          } else {
            igm.col(i)[iv[i]] += gv[i];
          }
        }
#ifdef GINN_ENABLE_GPU
      } else if constexpr (Kind == GPU) {
        Int rows = in_->value().rows();
        auto index_begin = thrust::device_ptr<Int>(index.data());
        auto ct_begin = thrust::make_counting_iterator(Int(0));
        auto map_begin = thrust::make_transform_iterator(
            make_zip_iterator(make_tuple(ct_begin, index_begin)),
            StridedIndex{rows});
        // If we had a "scatter_add" instead of "scatter", we wouldn't need
        // this additional temp tensor and the gather step. Maybe implement
        // based on thrust::scatter?
        Tensor<Scalar, Kind> grad_bits(dev(), grad().shape());
        thrust::gather(thrust::device,
                       map_begin,
                       map_begin + index.size(),
                       thrust::device_ptr<Raw<Scalar>>(grad_in.data()),
                       thrust::device_ptr<Raw<Scalar>>(grad_bits.data()));
        if (negate) {
          grad_bits -= grad().t();
        } else {
          grad_bits += grad().t();
        }
        auto grad_begin = thrust::device_ptr<Raw<Scalar>>(grad_bits.data());
        auto grad_end = grad_begin + grad_bits.size();
        thrust::scatter(thrust::device,
                        grad_begin,
                        grad_end,
                        map_begin,
                        thrust::device_ptr<Raw<Scalar>>(grad_in.data()));
#endif
      } else {
        GINN_THROW("Unexpected device!");
      }
    }
  }

  void check_range() {
    // TODO: Gpu
    if constexpr (Kind == CPU) {
      GINN_ASSERT((index_->value().v().array() >= Int(0)).all(),
                  "Picking index is negative!");
      GINN_ASSERT(
          (index_->value().v().array() < Int(in_->value().rows())).all(),
          "Picking index out of range!");
    }
  }

  void forward_() override {
    check_range();
    pick(in_->value());
  }

  void backward_() override { pick_grad(in_->grad()); }

 public:
  PickNode(const NodePtr<Scalar, Kind>& in, const DataPtr<Int, Kind>& index)
      : BaseDataNode<Scalar, Kind>(
            std::vector<BaseDevNodePtr<Kind>>{in, index}),
        in_(in),
        index_(index) {}

  PickNode(const NodePtr<Scalar, Kind>& in, const std::vector<Int>& index)
      : PickNode(in, Data<Int>(in->dev(), Shape{(Size)index.size()})) {
    index_->value().set(index);
  }

  PickNode(const NodePtr<Scalar, Kind>& in, Int index)
      : PickNode(in, std::vector<Int>{index}) {}

  std::string name() const override { return "Pick"; }
};

GINN_MAKE_SCALAR_FORWARDING_FACTORY(Pick);

template <typename Scalar, DeviceKind Kind>
class PickSoftmaxNode : public PickNode<Scalar, Kind> {
  // TODO: This can (possibly) be made more efficient by performing exp(x), then
  //   pick, then divide by sum(exp(x)), instead of picking at the end.
 protected:
  using PickNode<Scalar, Kind>::in_;
  Tensor<Scalar, Kind> smax_;

  void forward_() override {
    smax_ = smax_.copy_to(this->dev());
    smax_.resize(in_->value().shape());
    SoftmaxOp<Scalar, Kind>().forward(smax_, in_->value());
    this->pick(smax_);
  }

  void backward_() override {
    if (in_->has_grad()) {
      Tensor<Scalar, Kind> dsmax(smax_.dev(), smax_.shape(), Raw<Scalar>(0));
      this->pick_grad(dsmax);
      SoftmaxOp<Scalar, Kind>().backward(
          in_->grad(), dsmax, in_->value(), smax_, true);
    }
  }

 public:
  using PickNode<Scalar, Kind>::PickNode;

  std::string name() const override { return "PickSoftmax"; }
};

GINN_MAKE_SCALAR_FORWARDING_FACTORY(PickSoftmax);

template <typename Scalar, DeviceKind Kind>
class PickNegLogSoftmaxNode : public PickSoftmaxNode<Scalar, Kind> {
 protected:
  using PickSoftmaxNode<Scalar, Kind>::in_;
  using PickSoftmaxNode<Scalar, Kind>::smax_;
  Raw<Scalar> eps_{0};

  void forward_() override {
    if (eps_ == Raw<Scalar>(0)) {
      PickSoftmaxNode<Scalar, Kind>::forward_();
      value() = -value().t().log();
    } else {
      // TODO
    }
  }

  void backward_() override {
    if (in_->has_grad()) {
      if (eps_ == Raw<Scalar>(0)) {
        this->pick_grad(in_->grad(), /*negate*/ true);
        in_->grad() +=
            smax_.t() * grad().t().broadcast(Index<2>{smax_.rows(), 1});
      } else {
        // TODO
        // scores->grad() += (smax_.t() - eps_ / smax_.rows()) *
        //                  grad().t().broadcast(Index<2>{smax_.rows(), 1});
        // Real omeps = eps_ - 1.;
        // for (Size i = 0; i < smax_.cols(); i++) {
        //  Size j = index_.at(i);
        //  Lhs(dev(), scores->grad().view<3>().chip(i, 1).chip(j, 0)) +=
        //      grad().t().chip(i, 1) * omeps;
        //}
      }
    }
  }

 public:
  using PickSoftmaxNode<Scalar, Kind>::value;
  using PickSoftmaxNode<Scalar, Kind>::grad;

  using PickSoftmaxNode<Scalar, Kind>::PickSoftmaxNode;

  std::string name() const override { return "PickNegLogSoftmax"; }
};

GINN_MAKE_SCALAR_FORWARDING_FACTORY(PickNegLogSoftmax);

template <typename Scalar, DeviceKind Kind>
class PickNegLogSigmoidNode : public BaseDataNode<Scalar, Kind> {
 private:
  NodePtr<Scalar, Kind> in_;
  DataPtr<Int, Kind> index_;
  Tensor<Scalar, Kind> sigm_;
  // std::array<Real, 2> weights_{{1., 1.}}; // TODO:

  void forward_() override {
    auto& index = index_->value();
    // TODO: Maybe add a binary-ness check for index?

    sigm_.resize(in_->shape());
    SigmoidOp<Scalar, Kind>().forward(sigm_, in_->value());

    value().resize(sigm_.shape());
    // value() = -(index.t().template cast<Scalar>() * sigm_.t().log() +
    //            (Scalar(1) - index.t().template cast<Scalar>()) * (Scalar(1) -
    //            sigm_.t()).log());
    value() = -index.t().template cast<bool>().select(
        sigm_.t().log(), (Raw<Scalar>(1) - sigm_.t()).log());
  }

  void backward_() override {
    if (in_->has_grad()) {
      auto& index = index_->value();
      in_->grad() +=
          (sigm_.t() - index.t().template cast<Raw<Scalar>>()) * grad().t();
    }
  }

 public:
  using BaseDataNode<Scalar, Kind>::value;
  using BaseDataNode<Scalar, Kind>::grad;

  PickNegLogSigmoidNode(const NodePtr<Scalar, Kind>& in,
                        const DataPtr<Int, Kind>& index)
      : BaseDataNode<Scalar, Kind>(
            std::vector<BaseDevNodePtr<Kind>>{in, index}),
        in_(in),
        index_(index),
        sigm_(this->dev()) {}

  PickNegLogSigmoidNode(const NodePtr<Scalar, Kind>& in,
                        const std::vector<Int>& index)
      : PickNegLogSigmoidNode(in,
                              Data<Int>(in->dev(), Shape{(Size)index.size()})) {
    index_->value().set(index);
  }

  PickNegLogSigmoidNode(const NodePtr<Scalar, Kind>& in, Int index)
      : PickNegLogSigmoidNode(in, std::vector<Int>{index}) {}

  std::string name() const override { return "PickNegLogSigmoid"; }
};

GINN_MAKE_SCALAR_FORWARDING_FACTORY(PickNegLogSigmoid);
//
///* TODO
// class PickNegLogSoftmax2Node : public BaseDataNode {
//  // TODO: This is clearly inefficient because of the for loop.
//  // Any routines in Eigen? Write my own kernel? Also it is ugly.
//  // TODO: add GPU support
// public:
//  NodePtr scores, true_probs;
//  Tensor smax;
//  Real eps = 0;
//
//  void forward_() override {
//    GINN_ASSERT(dev()->kind() == CPU); // for now
//    smax.resize(scores->value().shape());
//    SoftmaxOp::forward(smax, scores->value());
//
//    value().resize({1, smax.cols()});
//
//    value().v() = -smax.m()
//        .array()
//        .log()
//        .matrix()
//        .cwiseProduct(true_probs->value().m())
//        .colwise()
//        .sum();
//  }
//
//  void backward_() override {
//    Tensor ones(smax.dev(), smax.shape());
//    ones.fill(1.);
//    scores->grad() += (smax.t() - true_probs->value().t()) *
//                      grad().t().broadcast(Index<2>{smax.rows(), 1});
//  }
//
//  PickNegLogSoftmax2Node(NodePtr a_scores, NodePtr a_true_probs)
//      : BaseDataNode(a_scores->dev(), {a_scores, a_true_probs}),
//        scores(a_scores),
//        true_probs(a_true_probs),
//        smax(a_scores->dev()) {}
//
//  std::string name() const override { return "PickNegLogSoftmax2"; }
//};
// */

} // namespace ginn

#endif // GINN_NODE_PICK_H

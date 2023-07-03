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

#ifndef GINN_NODE_REDUCE_H
#define GINN_NODE_REDUCE_H

#include <algorithm>

#include <ginn/node/data.h>

namespace ginn {

template <typename Scalar, DeviceKind Kind>
class SumNode : public BaseDataNode<Scalar, Kind> {
 private:
  NodePtr<Scalar, Kind> in_;

  void forward_() override { this->value() = in_->value().t().sum(); }
  void backward_() override {
    if (in_->has_grad()) {
      in_->grad() += this->grad().template view<1>().broadcast(
          Index<1>{in_->grad().size()});
    }
  }

 public:
  SumNode(const NodePtr<Scalar, Kind>& in)
      : BaseDataNode<Scalar, Kind>(in->dev(), {}, {in}), in_(in) {}

  void set_ins(const std::vector<BaseNodePtr>& ins) override {
    GINN_ASSERT(ins.size() == 1);
    BaseNode::ins_ = ins;
    in_ = dynamic_ptr_cast<Node<Scalar, Kind>>(ins.front());
  }

  std::string name() const override { return "Sum"; }
};

GINN_MAKE_SCALAR_FORWARDING_FACTORY(Sum);

template <typename Scalar, DeviceKind Kind>
class AxisSumNode : public BaseDataNode<Scalar, Kind> {
 private:
  NodePtr<Scalar, Kind> in_;
  std::vector<Size> axes_; // will be unique and sorted

  // TODO: Consider not viewing to max (8) before summing
  template <Size N>
  void forward_helper(const Index<N>& axes) {
    value() = in_->value().template view<8>().sum(axes);
  }

  template <Size N>
  void backward_helper(const Index<N>& axes) {
    Index<8> cast{1, 1, 1, 1, 1, 1, 1, 1};
    Shape s = grad().shape();
    for (Size i = 0; i < N; i++) {
      auto& axis = axes[i];
      s.insert(s.begin() + axis, 1);
      cast[axis] = in_->shape()[axis];
    }
    in_->grad() += grad().reshaped(s).template view<8>().broadcast(cast);
  }

  void forward_() override {
    Shape s, in_s = in_->shape();
    size_t i = 0;
    for (size_t j = 0; j < in_s.size(); j++) {
      if (i < axes_.size() and (Size) j == axes_[i]) {
        i++;
      } else {
        s.push_back(in_s[j]);
      }
    }
    value().resize(s);

    switch (axes_.size()) {
    case 1: forward_helper<1>(ShapeToIndex<1>(axes_)); break;
    case 2: forward_helper<2>(ShapeToIndex<2>(axes_)); break;
    case 3: forward_helper<3>(ShapeToIndex<3>(axes_)); break;
    case 4: forward_helper<4>(ShapeToIndex<4>(axes_)); break;
    case 5: forward_helper<5>(ShapeToIndex<5>(axes_)); break;
    case 6: forward_helper<6>(ShapeToIndex<6>(axes_)); break;
    case 7: forward_helper<7>(ShapeToIndex<7>(axes_)); break;
    case 8: forward_helper<8>(ShapeToIndex<8>(axes_)); break;
    default: GINN_THROW("Unexpected number of axes in AxisSum");
    }
  }

  void backward_() override {
    if (in_->has_grad()) {
      switch (axes_.size()) {
      case 1: backward_helper<1>(ShapeToIndex<1>(axes_)); break;
      case 2: backward_helper<2>(ShapeToIndex<2>(axes_)); break;
      case 3: backward_helper<3>(ShapeToIndex<3>(axes_)); break;
      case 4: backward_helper<4>(ShapeToIndex<4>(axes_)); break;
      case 5: backward_helper<5>(ShapeToIndex<5>(axes_)); break;
      case 6: backward_helper<6>(ShapeToIndex<6>(axes_)); break;
      case 7: backward_helper<7>(ShapeToIndex<7>(axes_)); break;
      case 8: backward_helper<8>(ShapeToIndex<8>(axes_)); break;
      default: GINN_THROW("Unexpected number of axes in AxisSum");
      }
    }
  }

 public:
  using BaseDataNode<Scalar, Kind>::value;
  using BaseDataNode<Scalar, Kind>::grad;

  AxisSumNode(const NodePtr<Scalar, Kind>& in, std::vector<Size> axes)
      : BaseDataNode<Scalar, Kind>({in}), in_(in), axes_(std::move(axes)) {
    GINN_ASSERT(std::is_sorted(axes_.begin(), axes_.end()),
                "Axes need to be specified in sorted order in AxisSum!");
    GINN_ASSERT(std::unique(axes_.begin(), axes_.end()) == axes_.end(),
                "Axes need to be uniquely specified in AxisSum!");
  }

  std::string name() const override { return "AxisSum"; }
};

GINN_MAKE_SCALAR_FORWARDING_FACTORY(AxisSum);

template <typename NodePtrType>
auto AxisSum(const NodePtrType& in, std::initializer_list<Size> axes) {
  return AxisSum(in, std::vector<Size>(axes));
}

template <typename Scalar, DeviceKind Kind>
class MeanNode : public BaseDataNode<Scalar, Kind> {
 private:
  NodePtr<Scalar, Kind> in_;

  void forward_() override {
    this->value().resize({});
    this->value() = in_->value().t().mean();
  }
  void backward_() override {
    if (in_->has_grad()) {
      auto size = in_->value().size();
      in_->grad() += this->grad().template view<1>().broadcast(Index<1>{size}) /
                     Raw<Scalar>(size);
    }
  }

 public:
  MeanNode(const NodePtr<Scalar, Kind>& in)
      : BaseDataNode<Scalar, Kind>({in}), in_(in) {}

  std::string name() const override { return "Mean"; }
};

GINN_MAKE_SCALAR_FORWARDING_FACTORY(Mean);

template <typename Scalar, DeviceKind Kind>
class VarianceNode : public BaseDataNode<Scalar, Kind> {
 private:
  NodePtr<Scalar, Kind> in_;
  Tensor<Scalar, Kind> mean_;

  void forward_() override {
    mean_ = in_->value().t().mean();
    value() =
        (in_->value().template view<1>() -
         mean_.template view<1>().broadcast(Index<1>{in_->value().size()}))
            .square()
            .eval()
            .mean();
  }
  void backward_() override {
    if (in_->has_grad()) {
      auto size = in_->value().size();
      in_->grad() += (in_->value().template view<1>() -
                      mean_.template view<1>().broadcast(Index<1>{size})) *
                     grad().template view<1>().broadcast(Index<1>{size}) *
                     Raw<Scalar>(2. / size);
    }
  }

 public:
  using BaseDataNode<Scalar, Kind>::value;
  using BaseDataNode<Scalar, Kind>::grad;

  VarianceNode(const NodePtr<Scalar, Kind>& in)
      : BaseDataNode<Scalar, Kind>(in->dev(), {}, {in}),
        in_(in),
        mean_(this->dev(), Shape{}) {}

  std::string name() const override { return "Variance"; }
};

GINN_MAKE_SCALAR_FORWARDING_FACTORY(Variance);

} // namespace ginn

#endif

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

#ifndef GINN_NODE_LAYOUT_H
#define GINN_NODE_LAYOUT_H

#include <cppitertools/chain.hpp>
#include <cppitertools/imap.hpp>

#include <ginn/node.h>
#include <ginn/node/data.h>

#ifdef GINN_ENABLE_GPU

#include <cuda_fp16.h>
#include <thrust/functional.h>
#include <thrust/tabulate.h>

// helper for ginn::Half / Eigen::half to use raw fp16
inline __device__ auto atomicAdd(Eigen::half* out, Eigen::half val) {
  return atomicAdd(reinterpret_cast<__half*>(out), static_cast<__half>(val));
}

// helper for UpperTri
template <typename Scalar>
struct UpperTriHelper {
  long s;
  inline __device__ auto operator()(long i) {
    auto col = i / s;
    auto row = i % s;
    return Scalar(row <= col);
  }
};

#endif

namespace ginn {

class SinkNode : public BaseNode {
 public:
  using BaseNode::BaseNode;

  Shape shape() const override {
    GINN_THROW("Sink has no shape!");
    return {};
  }

  std::string name() const override { return "Sink"; }
};

GINN_MAKE_FACTORY(Sink);
GINN_FORWARD_INIT_LIST(Sink, BaseNodePtr);

class DimNode : public BaseNode {
 protected:
  Size dim_ = 0;
  Size index_ = 0;

  void forward_() override {
    if (not ins().empty()) { dim_ = in()->shape().at(index_); }
  }

 public:
  DimNode() = default;
  DimNode(Size n) : dim_(n) {}
  DimNode(BaseNodePtr e, Size index)
      : BaseNode(std::vector<BaseNodePtr>{e}), index_(index) {}

  bool has_grad() const override { return false; }

  Size value() { return dim_; };

  Shape shape() const override {
    GINN_THROW("Dim has no shape!");
    return {};
  }

  std::string name() const override { return "Dim"; }
};

using DimPtr = Ptr<DimNode>;

GINN_MAKE_FACTORY(Dim);

class DimProdNode : public DimNode {
 private:
  DimPtr left_, right_;

  void forward_() override { dim_ = left_->value() * right_->value(); }

 public:
  DimProdNode(DimPtr left, DimPtr right)
      : left_(std::move(left)), right_(std::move(right)) {
    ins_ = {left_, right_};
  }

  std::string name() const override { return "DimProd"; }
};

GINN_MAKE_FACTORY(DimProd);
auto operator*(DimPtr a, DimPtr b) { return DimProd(a, b); }

 template <typename Scalar, DeviceKind Kind>
 class DeviceViewNode : public Node<Scalar, Kind> {
  private:
   NodePtr<Scalar, Kind> in_;
   DevPtr<Kind> dev_;

  public:
   DeviceViewNode(const NodePtr<Scalar, Kind>& e, DevPtr<Kind> dev)
       : Node<Scalar, Kind>(std::vector{e}), in_(e), dev_(std::move(dev)) {
   }
   DevPtr<Kind> dev() const override { return dev_; }

   const Tensor<Scalar, Kind>& value() const override { return in_->value(); }
   const Tensor<Scalar, Kind>& grad() const override { return in_->grad(); }

   bool has_grad() const override { return in_->has_grad(); }
   void init_grad() override { in_->init_grad(); }
   void reset_grad() override { in_->reset_grad(); }
   void reset_forwarded() override { in_->reset_forwarded(); }

   std::string name() const override { return "DeviceView"; }
 };

 GINN_MAKE_SCALAR_FORWARDING_FACTORY(DeviceView);
//
// template <typename Scalar, DeviceKind TgtKind, DeviceKind SrcKind>
// class DeviceTransferNode : public BaseDataNode<Scalar, SrcKind> {
//  private:
//   NodePtr<Scalar, SrcKind> in_;
//
//   void forward_() override { this->value() = in_->value(); }
//   void backward_() override {
//     if (in_->has_grad()) {
//       // TODO: How to safely avoid copy here if we can know lhs is singular
//       // such that = and += would be the same?
//       in_->grad() += this->grad().maybe_copy_to(in_->dev()).t();
//     }
//   }
//
//  public:
//   DeviceTransferNode(NodePtr<Scalar, SrcKind> e, DevPtr<TgtKind> dev)
//       : BaseDataNode<Scalar, TgtKind>(dev, {e}), in_(e) {}
//
//   // TODO: is the following correct?
//   bool has_grad() const override { return in_->has_grad(); }
//
//   std::string name() const override { return "DeviceTransfer"; }
// };
//
// GINN_MAKE_SCALAR_FORWARDING_FACTORY(DeviceTransfer);
//
template <typename Scalar, DeviceKind Kind>
class CatNode : public BaseDataNode<Scalar, Kind> {
 private:
  std::vector<NodePtr<Scalar, Kind>> ins_;

  void forward_() override {
    Size rows = 0;
    for (auto in : ins_) { rows += in->value().rows(); }
    value().resize({rows, (Size)ins_[0]->value().cols()});

    rows = 0;
    for (auto in : ins_) {
      auto dim = in->value().shape2();
      value().slice(Index<2>{rows, 0}, Index<2>{dim[0], dim[1]}) =
          in->value().t();
      rows += dim[0];
    }

    // TODO: Resize to original rank of the input
  }

  void backward_() override {
    Size rows = 0;
    for (auto in : ins_) {
      auto dim = in->grad().shape2();
      if (in->has_grad()) {
        in->grad() +=
            grad().t().slice(Index<2>{rows, 0}, Index<2>{dim[0], dim[1]});
      }
      rows += dim[0];
    }
  }

 public:
  using BaseDataNode<Scalar, Kind>::value;
  using BaseDataNode<Scalar, Kind>::grad;

  CatNode(const std::vector<NodePtr<Scalar, Kind>>& ins)
      : BaseDataNode<Scalar, Kind>(ins), ins_(ins) {}
  template <typename... Args>
  CatNode(const NodePtr<Scalar, Kind>& in, Args&&... args)
      : BaseDataNode<Scalar, Kind>(
            std::vector<NodePtr<Scalar, Kind>>{in, args...}),
        ins_(std::vector<NodePtr<Scalar, Kind>>{in, args...}) {}

  std::string name() const override { return "Cat"; }
};

GINN_MAKE_SCALAR_FORWARDING_FACTORY(Cat);

// This is helpful when batching. In most cases we can assume that the
// 'column' dimension of a rank 2 view is the batch dimension.
template <typename Scalar, DeviceKind Kind>
class RowwiseCatNode : public BaseDataNode<Scalar, Kind> {
 private:
  std::vector<NodePtr<Scalar, Kind>> ins_;
  std::vector<Size> offsets_, extents_;

  void forward_() override {
    Size cols = 0;
    for (auto in : ins_) { cols += in->value().cols(); }
    value().resize({(Size)ins_[0]->value().rows(), cols});

    cols = 0;
    for (auto in : ins_) {
      auto dim = in->value().shape2();
      value().slice(Index<2>{0, cols}, Index<2>{dim[0], dim[1]}) =
          in->value().t();
      offsets_.push_back(cols);
      extents_.push_back(dim[1]);
      cols += dim[1];
    }
  }

  void backward_() override {
    Size cols = 0;
    for (auto in : ins_) {
      auto dim = in->grad().shape2();
      if (in->has_grad()) {
        in->grad() +=
            grad().t().slice(Index<2>{0, cols}, Index<2>{dim[0], dim[1]});
      }
      cols += dim[1];
    }
  }

 public:
  using BaseDataNode<Scalar, Kind>::value;
  using BaseDataNode<Scalar, Kind>::grad;

  const std::vector<Size>& offsets() const { return offsets_; }
  const std::vector<Size>& extents() const { return extents_; }

  RowwiseCatNode(const std::vector<NodePtr<Scalar, Kind>>& ins)
      : BaseDataNode<Scalar, Kind>(ins), ins_(ins) {}
  template <typename... Args>
  RowwiseCatNode(const NodePtr<Scalar, Kind>& in, Args&&... args)
      : RowwiseCatNode(std::vector<NodePtr<Scalar, Kind>>{in, args...}) {}

  std::string name() const override { return "RowwiseCat"; }
};

GINN_MAKE_SCALAR_FORWARDING_FACTORY(RowwiseCat);

// RowwiseUncatNode is meant to be used during autobatching. Autobatching
// mechanism needs to know where each instance came from during RowwiseCat, to
// be able to redistribute them after batched operations.
template <typename Scalar, DeviceKind Kind>
class RowwiseUncatNode : public BaseDataNode<Scalar, Kind> {
 private:
  NodePtr<Scalar, Kind> in_;
  Size index_;
  Ptr<RowwiseCatNode<Scalar, Kind>> cat_;

  void forward_() override {
    Size offset = cat_->offsets().at(index_);
    Size extent = cat_->extents().at(index_);
    Size rows = in_->value().rows();

    value().map(in_->value(), {rows, extent}, rows * offset);
  }

 public:
  using BaseDataNode<Scalar, Kind>::value;
  using BaseDataNode<Scalar, Kind>::grad;

  bool has_grad() const override { return in_->has_grad(); }

  void init_grad() override {
    if (has_grad()) {
      Size offset = cat_->offsets().at(index_);
      Size extent = cat_->extents().at(index_);
      Size rows = in_->value().rows();

      grad().map(in_->grad(), {rows, extent}, rows * offset);
    }
  }

  RowwiseUncatNode(const NodePtr<Scalar, Kind>& in,
                   Size index,
                   Ptr<RowwiseCatNode<Scalar, Kind>> cat)
      : BaseDataNode<Scalar, Kind>(in),
        in_(in),
        index_(index),
        cat_(std::move(cat)) {
    BaseNode::ins_.push_back(cat_);
  }

  std::string name() const override { return "RowwiseUncat"; }
};

GINN_MAKE_SCALAR_FORWARDING_FACTORY(RowwiseUncat);

template <typename NestedContainer>
auto flatten(NestedContainer&& mat) {
  return iter::chain.from_iterable(std::forward<NestedContainer>(mat));
}

#ifdef GINN_ENABLE_GPU

template <typename Scalar>
__global__ void stack_helper(Scalar* out,  // total length is sz * m * n
                             Scalar** ins, // m * n -long list of sz-long arrays
                             const Size sz,
                             const Size mn) {
  Size index = blockIdx.x * blockDim.x + threadIdx.x;
  Size stride = blockDim.x * gridDim.x;
  Size total = sz * mn;

  for (auto i = index; i < total; i += stride) { out[i] = ins[i / sz][i % sz]; }
}

template <typename Scalar>
__global__ void stack_backward_helper(Scalar** d_ins,
                                      Scalar* d_out,
                                      const Size sz,
                                      const Size mn) {
  Size index = blockIdx.x * blockDim.x + threadIdx.x;
  Size stride = blockDim.x * gridDim.x;
  Size total = sz * mn;

  for (auto i = index; i < total; i += stride) {
    atomicAdd(&d_ins[i / sz][i % sz], d_out[i]);
  }
}
#endif

template <typename Scalar, DeviceKind Kind>
class StackNode : public BaseDataNode<Scalar, Kind> {
  // TODO: Make this generic of input rank instead of fixing to 2
  // TODO: Add deduction hints to avoid typing in Scalar types when using
  //   initializer lists
 private:
  std::vector<std::vector<NodePtr<Scalar, Kind>>> nodes_;

  void forward_() override {
    Size m = nodes_.size();
    Size n = nodes_[0].size();
    auto s = nodes_[0][0]->shape();
    for (auto& inner : nodes_) {
      for (auto& x : inner) {
        GINN_ASSERT(x->shape() == s, "Input shapes mismatch!");
      }
    }

    Shape ns = s + Shape{m, n};
    value().resize(ns);
    Size sz = nodes_[0][0]->size();

    if (dev()->kind() == CPU) {
      auto view = value().reshaped({sz, m, n});
      for (Size i = 0; i < m; i++) {
        for (Size j = 0; j < n; j++) {
          auto in_view = nodes_[i][j]->value().reshaped({sz, 1, 1});
          view.slice(Index<3>{0, i, j}, Index<3>{sz, 1, 1}) =
              in_view.template view<3>();
        }
      }
#ifdef GINN_ENABLE_GPU
    } else if (dev()->kind() == GPU) {
      std::vector<Raw<Scalar>*> ins_flat(m * n);
      for (Size i = 0; i < m; i++) {
        for (Size j = 0; j < n; j++) {
          ins_flat[j * m + i] = nodes_[i][j]->value().data();
        }
      }
      thrust::device_vector<Raw<Scalar>*> ins_flat_d(ins_flat);
      int blockSize = 256;
      int numBlocks = (m * n * sz + blockSize - 1) / blockSize;
      stack_helper<<<numBlocks, blockSize>>>(
          value().data(),
          thrust::raw_pointer_cast(ins_flat_d.data()),
          sz,
          m * n);
#endif
    } else {
      GINN_THROW("Unexpected device!");
    }
  }

  void backward_() override {
    Size m = nodes_.size();
    Size n = nodes_[0].size();
    Size sz = nodes_[0][0]->size();
    if (dev()->kind() == CPU) {
      auto view = grad().reshaped({sz, m, n});
      for (Size i = 0; i < m; i++) {
        for (Size j = 0; j < n; j++) {
          if (nodes_[i][j]->has_grad()) {
            auto in_view = nodes_[i][j]->grad().reshaped({sz, 1, 1});
            in_view += view.template view<3>().slice(Index<3>{0, i, j},
                                                     Index<3>{sz, 1, 1});
          }
        }
      }
#ifdef GINN_ENABLE_GPU
    } else if (dev()->kind() == GPU) {
      std::vector<Raw<Scalar>*> d_ins_flat(m * n);
      thrust::device_vector<Raw<Scalar>> dummy_in(sz);
      for (Size i = 0; i < m; i++) {
        for (Size j = 0; j < n; j++) {
          if (nodes_[i][j]->has_grad()) {
            d_ins_flat[j * m + i] = nodes_[i][j]->grad().data();
          } else {
            d_ins_flat[j * m + i] = thrust::raw_pointer_cast(dummy_in.data());
          }
        }
      }
      thrust::device_vector<Raw<Scalar>*> d_ins_flat_d(d_ins_flat);
      int blockSize = 256;
      int numBlocks = (m * n * sz + blockSize - 1) / blockSize;
      stack_backward_helper<<<numBlocks, blockSize>>>(
          thrust::raw_pointer_cast(d_ins_flat_d.data()),
          grad().data(),
          sz,
          m * n);
#endif
    } else {
      GINN_THROW("Unexpected device!");
    }
  }

 public:
  using BaseDataNode<Scalar, Kind>::value;
  using BaseDataNode<Scalar, Kind>::grad;
  using BaseDataNode<Scalar, Kind>::dev;

  StackNode(const std::vector<std::vector<NodePtr<Scalar, Kind>>>& nodes)
      : BaseDataNode<Scalar, Kind>(flatten(nodes)), nodes_(nodes) {
    GINN_ASSERT(not nodes_.empty(), "Empty input to Stack!");
    GINN_ASSERT(not nodes_.front().empty(), "Empty input to Stack!");
    for (auto& inner : nodes_) {
      GINN_ASSERT(inner.size() == nodes_.front().size(),
                  "Inner container sizes mismatch!");
    }
  }

  std::string name() const override { return "Stack"; }
};

template <typename Scalar, DeviceKind Kind>
auto Stack(const std::vector<std::vector<NodePtr<Scalar, Kind>>>& ins) {
  return make_ptr<StackNode<Scalar, Kind>>(ins);
}

template <typename T>
auto Stack(std::initializer_list<std::initializer_list<T>> ins) {
  using Scalar = typename T::element_type::Scalar;
  static const auto Kind = T::element_type::device_kind;
  std::vector<std::vector<NodePtr<Scalar, Kind>>> v;

  for (auto& inner : ins) { v.emplace_back(inner.begin(), inner.end()); }
  return Stack(v);
}

template <typename Scalar, DeviceKind Kind>
class ReshapeNode : public BaseDataNode<Scalar, Kind> {
 public:
  using LazyShape = std::vector<DimPtr>;

 private:
  NodePtr<Scalar, Kind> in_;
  LazyShape s_;

  static Shape to_shape(const LazyShape& ls) {
    return vector(iter::imap([](auto&& x) { return x->value(); }, ls));
  }

  static LazyShape to_lazy_shape(const Shape& s) {
    return vector(iter::imap([](auto d) { return Dim(d); }, s));
  }

  void forward_() override { value().map(in_->value(), to_shape(s_)); }

 public:
  using BaseDataNode<Scalar, Kind>::value;
  using BaseDataNode<Scalar, Kind>::grad;

  ReshapeNode(NodePtr<Scalar, Kind> in, Shape s)
      : ReshapeNode(std::move(in), to_lazy_shape(std::move(s))) {}

  ReshapeNode(const NodePtr<Scalar, Kind>& in, const LazyShape& s)
      : BaseDataNode<Scalar, Kind>(in), in_(in), s_(s) {
    for (auto& x : s_) { BaseNode::ins_.push_back(x); }
  }

  bool has_grad() const override { return in_->has_grad(); }

  // TODO: I think the following method fails for composing consecutive
  //   Reshape nodes. Either fix or disallow.
  void init_grad() override {
    if (has_grad()) {
      in_->init_grad();
      grad().map(in_->grad(), to_shape(s_));
    }
  }

  std::string name() const override { return "Reshape"; }
};

GINN_MAKE_SCALAR_FORWARDING_FACTORY(Reshape);

template <typename Node>
auto Reshape(Ptr<Node> in, std::initializer_list<DimPtr> s) {
  return Reshape(in, std::vector<DimPtr>(s));
}

template <typename Scalar, DeviceKind Kind>
class RankViewNode : public BaseDataNode<Scalar, Kind> {
  // TODO: Handle rank-0 case
 private:
  NodePtr<Scalar, Kind> in_;
  Size rank_;

  void forward_() override {
    value().map(in_->value(), Tensor<>::reduce(in_->shape(), rank_));
  }

  void backward_() override {}

 public:
  RankViewNode(NodePtr<Scalar, Kind> in, Size rank)
      : BaseDataNode<Scalar, Kind>(in), in_(in), rank_(rank) {}

  using BaseDataNode<Scalar, Kind>::value;
  using BaseDataNode<Scalar, Kind>::grad;
  using BaseDataNode<Scalar, Kind>::has_grad;

  bool has_grad() const override { return in_->has_grad(); }

  void init_grad() override {
    if (has_grad()) {
      in_->init_grad();
      grad().map(in_->grad(), Tensor<>::reduce(in_->shape(), rank_));
    }
  }

  std::string name() const override { return "RankView"; }
};

GINN_MAKE_SCALAR_FORWARDING_FACTORY(RankView);

template <typename Scalar, DeviceKind Kind>
class SliceNode : public BaseDataNode<Scalar, Kind> {
 private:
  NodePtr<Scalar, Kind> in_;
  Shape offsets_, sizes_;

  template <int N>
  void forward_helper() {
    value() = in_->value().template view<N>().slice(ShapeToIndex<N>(offsets_),
                                                    ShapeToIndex<N>(sizes_));
  }

  template <int N>
  void backward_helper() {
    in_->grad().slice(ShapeToIndex<N>(offsets_), ShapeToIndex<N>(sizes_)) +=
        grad().template view<N>();
  }

  void forward_() override {
    value().resize(sizes_);
    switch (sizes_.size()) {
    case 1: forward_helper<1>(); break;
    case 2: forward_helper<2>(); break;
    case 3: forward_helper<3>(); break;
    case 4: forward_helper<4>(); break;
    case 5: forward_helper<5>(); break;
    case 6: forward_helper<6>(); break;
    case 7: forward_helper<7>(); break;
    case 8: forward_helper<8>(); break;
    default: GINN_THROW("Unexpected number of indices in Slice!");
    }
  }

  void backward_() override {
    if (in_->has_grad()) {
      switch (sizes_.size()) {
      case 1: backward_helper<1>(); break;
      case 2: backward_helper<2>(); break;
      case 3: backward_helper<3>(); break;
      case 4: backward_helper<4>(); break;
      case 5: backward_helper<5>(); break;
      case 6: backward_helper<6>(); break;
      case 7: backward_helper<7>(); break;
      case 8: backward_helper<8>(); break;
      default: GINN_THROW("Unexpected number of indices in Slice!");
      }
    }
  }

 public:
  using BaseDataNode<Scalar, Kind>::value;
  using BaseDataNode<Scalar, Kind>::grad;
  using BaseDataNode<Scalar, Kind>::has_grad;

  SliceNode(const NodePtr<Scalar, Kind>& x, Shape offsets, Shape sizes)
      : BaseDataNode<Scalar, Kind>(x),
        in_(x),
        offsets_(std::move(offsets)),
        sizes_(std::move(sizes)) {
    GINN_ASSERT(offsets_.size() == sizes_.size());
  }

  std::string name() const override { return "Slice"; }
};

GINN_MAKE_SCALAR_FORWARDING_FACTORY(Slice);

template <typename Scalar, DeviceKind Kind>
class ChipNode : public BaseDataNode<Scalar, Kind> {
  // TODO: If chipping from rightmost dimension, we can simply map into the
  // original input tensor instead of making a copy.
 private:
  NodePtr<Scalar, Kind> in_;
  Size offset_, dim_;

  template <int N>
  void forward_helper() {
    value() = in_->value().template view<N>().chip(offset_, dim_);
  }

  template <int N>
  void backward_helper() {
    in_->grad().template chip<N>(offset_, dim_) +=
        grad().template view<N - 1>();
  }

  void forward_() override {
    GINN_ASSERT(dim_ >= 0 and size_t(dim_) < in_->shape().size());
    GINN_ASSERT(offset_ >= 0 and offset_ < in_->shape()[dim_]);

    Shape s = in_->shape();
    s.erase(s.begin() + dim_);
    value().resize(s);

    switch (in_->shape().size()) {
    // case 1: forward_helper<1>(); break;
    case 2: forward_helper<2>(); break;
    case 3: forward_helper<3>(); break;
    case 4: forward_helper<4>(); break;
    case 5: forward_helper<5>(); break;
    case 6: forward_helper<6>(); break;
    case 7: forward_helper<7>(); break;
    case 8: forward_helper<8>(); break;
    default: GINN_THROW("Unexpected input rank in Chip!");
    }
  }

  void backward_() override {
    if (in_->has_grad()) {
      switch (in_->shape().size()) {
      // case 1: backward_helper<1>(); break;
      case 2: backward_helper<2>(); break;
      case 3: backward_helper<3>(); break;
      case 4: backward_helper<4>(); break;
      case 5: backward_helper<5>(); break;
      case 6: backward_helper<6>(); break;
      case 7: backward_helper<7>(); break;
      case 8: backward_helper<8>(); break;
      default: GINN_THROW("Unexpected grad rank in Chip!");
      }
    }
  }

 public:
  using BaseDataNode<Scalar, Kind>::value;
  using BaseDataNode<Scalar, Kind>::grad;

  ChipNode(const NodePtr<Scalar, Kind>& x, Size offset, Size dim)
      : BaseDataNode<Scalar, Kind>(x), in_(x), offset_(offset), dim_(dim) {}

  std::string name() const override { return "Chip"; }
};

GINN_MAKE_SCALAR_FORWARDING_FACTORY(Chip);
//
// template <typename Scalar>
// class MapNode : public BaseDataNode<Scalar> {
//  // TODO: how does Map work with has_grad? forwarded?
// private:
//  NodePtr<Scalar> in_;
//
// public:
//  const Tensor<Scalar>& value() const override { return in_->value(); }
//  const Tensor<Scalar>& grad() const override { return in_->grad(); }
//  bool has_grad() const override { return in_->has_grad(); }
//
//  MapNode(NodePtr<Scalar> x) : BaseDataNode<Scalar>({x}), in_(x) {}
//
//  void set_ins(const std::vector<BaseNodePtr>& ins) override {
//    GINN_ASSERT(ins.size() == 1);
//    BaseNode::ins_ = ins;
//    in_ = dynamic_ptr_cast<Node<Scalar>>(ins.front());
//    GINN_ASSERT(in_);
//  }
//
//  std::string name() const override { return "Map"; }
//};
//
// GINN_MAKE_SCALAR_FORWARDING_FACTORY(Map);
//
template <typename Scalar, DeviceKind Kind>
class PermuteNode : public BaseDataNode<Scalar, Kind> {
 protected:
  NodePtr<Scalar, Kind> in_;
  Shape indices_;
  bool overwrite_ = false; // to be used with InPlacePermuteNode derived class

  // inverse permutation of a shape
  static Shape inverse(const Shape& perm) {
    Shape inv(perm.size());
    for (size_t i = 0; i < perm.size(); i++) { inv[perm[i]] = i; }
    return inv;
  }

  // check if a shape is a permutation of 0, 1, ..., N-1
  bool check_permutation() {
    Shape incr(indices_.size());
    std::iota(incr.begin(), incr.end(), 0);
    return std::is_permutation(indices_.begin(), indices_.end(), incr.begin());
  }

  static Shape permute(const Shape& s, const Shape& perm) {
    Shape new_s(s.size());
    std::transform(
        perm.begin(), perm.end(), new_s.begin(), [&](Size i) { return s[i]; });
    return new_s;
  }

  template <Size N>
  void forward_helper() {
    if (overwrite_) {
      value() = in_->value()
                    .template view<N>()
                    .shuffle(ShapeToIndex<N>(indices_))
                    .eval();
    } else {
      value() =
          in_->value().template view<N>().shuffle(ShapeToIndex<N>(indices_));
    }
  }
  template <Size N>
  void backward_helper() {
    if (overwrite_) { // This case is meant for InPlacePermuteNode
      in_->grad() = grad()
                        .template view<N>()
                        .shuffle(ShapeToIndex<N>(inverse(indices_)))
                        .eval();
    } else {
      in_->grad() +=
          grad().template view<N>().shuffle(ShapeToIndex<N>(inverse(indices_)));
    }
  }

  void forward_() override {
    GINN_ASSERT(indices_.size() == in_->shape().size());
    GINN_ASSERT(check_permutation(),
                "Indices are not a proper permutation in Permute!");

    Shape s = permute(in_->shape(), indices_);
    value().resize(s);

    switch (indices_.size()) {
    case 2: forward_helper<2>(); break;
    case 3: forward_helper<3>(); break;
    case 4: forward_helper<4>(); break;
    case 5: forward_helper<5>(); break;
    case 6: forward_helper<6>(); break;
    case 7: forward_helper<7>(); break;
    case 8: forward_helper<8>(); break;
    default: GINN_THROW("Unexpected number of indices in Permute!");
    }
  }

  void backward_() override {
    if (in_->has_grad()) {
      switch (indices_.size()) {
      case 2: backward_helper<2>(); break;
      case 3: backward_helper<3>(); break;
      case 4: backward_helper<4>(); break;
      case 5: backward_helper<5>(); break;
      case 6: backward_helper<6>(); break;
      case 7: backward_helper<7>(); break;
      case 8: backward_helper<8>(); break;
      default: GINN_THROW("Unexpected number of indices in Permute!");
      }
    }
  }

 public:
  using BaseDataNode<Scalar, Kind>::value;
  using BaseDataNode<Scalar, Kind>::grad;

  PermuteNode(const NodePtr<Scalar, Kind>& in, Shape indices)
      : BaseDataNode<Scalar, Kind>(in), in_(in), indices_(std::move(indices)) {}

  std::string name() const override { return "Permute"; }
};

GINN_MAKE_SCALAR_FORWARDING_FACTORY(Permute);

template <typename NodePtrType>
auto Transpose(const NodePtrType& x, Size i, Size j) {
  Shape indices(x->shape().size());
  std::iota(indices.begin(), indices.end(), 0);
  std::swap(indices.at(i), indices.at(j));
  return Permute(std::move(x), std::move(indices));
}

template <typename Scalar, DeviceKind Kind>
class RowBroadcastNode : public BaseDataNode<Scalar, Kind> {
 private:
  NodePtr<Scalar, Kind> in_;
  DimPtr rows_;

  virtual void forward_() override {
    auto& x = in_->value();
    GINN_ASSERT(x.shape().size() == 2);
    GINN_ASSERT(x.rows() == 1);

    Size rows = rows_->value();
    this->value().resize({rows, x.cols()});
    this->value() = x.t().broadcast(Index<2>{rows, 1});
  }

  virtual void backward_() override {
    if (in_->has_grad()) { in_->grad() += this->grad().t().sum(Index<1>{0}); }
  }

 public:
  RowBroadcastNode(const NodePtr<Scalar, Kind>& in, DimPtr rows)
      : BaseDataNode<Scalar, Kind>(in), in_(in), rows_(std::move(rows)) {
    BaseNode::ins_.push_back(rows_);
  }
  RowBroadcastNode(NodePtr<Scalar, Kind> in, Size rows)
      : RowBroadcastNode(std::move(in), make_ptr<DimNode>(rows)) {}

  std::string name() const override { return "RowBroadcast"; }
};

GINN_MAKE_SCALAR_FORWARDING_FACTORY(RowBroadcast);

template <typename Scalar, DeviceKind Kind>
class ColBroadcastNode : public BaseDataNode<Scalar, Kind> {
 private:
  NodePtr<Scalar, Kind> in_;
  DimPtr cols_;

  virtual void forward_() override {
    auto& x = in_->value();
    GINN_ASSERT(x.cols() == 1);

    Size cols = cols_->value();
    if (cols > 1) {
      value().resize({x.rows(), cols});
      value() = x.t().broadcast(Index<2>{1, cols});
    } else { // No need to make a copy. Refer to the input instead.
      value().map(in_->value(), in_->value().shape());
    }
  }

  void backward_() override {
    if (in_->has_grad() and cols_->value() > 1) {
      in_->grad() += grad().t().sum(Index<1>{1});
    }
  }

 public:
  ColBroadcastNode(const NodePtr<Scalar, Kind>& in, DimPtr cols)
      : BaseDataNode<Scalar, Kind>(in), in_(in), cols_(std::move(cols)) {
    BaseNode::ins_.push_back(cols_);
  }
  ColBroadcastNode(NodePtr<Scalar, Kind> in, Size cols)
      : ColBroadcastNode(std::move(in), make_ptr<DimNode>(cols)) {}

  using BaseDataNode<Scalar, Kind>::value;
  using BaseDataNode<Scalar, Kind>::grad;

  bool has_grad() const override {
    if (cols_->value() == 1) { return in_->has_grad(); }
    return BaseDataNode<Scalar, Kind>::has_grad();
  }

  void init_grad() override {
    if (has_grad()) {
      if (cols_->value() > 1) {
        if (grad().shape() != value().shape()) {
          grad().resize(value().shape());
        }
      } else {
        grad().map(in_->grad(), in_->grad().shape());
      }
    }
  }

  std::string name() const override { return "ColBroadcast"; }
};

GINN_MAKE_SCALAR_FORWARDING_FACTORY(ColBroadcast);

template <typename Scalar, DeviceKind Kind>
class UpperTriNode : public BaseDataNode<Scalar, Kind> {
 public:
  using BaseDataNode<Scalar, Kind>::value;

 private:
  DimPtr size_; // value() is of shape {size_, size_} (i.e. matrix)

  void forward_() override {
    auto s = size_->value();
    value().resize({s, s});
    if (this->dev()->kind() == CPU) {
      value().set_ones();
      value().m() = value().m().template triangularView<Eigen::Upper>();
#ifdef GINN_ENABLE_GPU
    } else if (this->dev()->kind() == GPU) {
      auto begin = thrust::device_ptr<Scalar>(value().data());
      auto end = begin + value().size();
      thrust::tabulate(begin, end, UpperTriHelper<Scalar>{s});
#endif
    } else {
      GINN_THROW("Unexpected device!");
    }
  }

 public:
  bool has_grad() const override { return false; }

  UpperTriNode(DevPtr<Kind> dev, DimPtr size)
      : BaseDataNode<Scalar, Kind>(std::move(dev), {size}), size_(size) {}
  UpperTriNode(DevPtr<Kind> dev, Size size)
      : UpperTriNode(std::move(dev), Dim(size)) {}

  std::string name() const override { return "UpperTri"; }
};

GINN_MAKE_TEMPLATE_FACTORY(UpperTri);

} // namespace ginn

#endif

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

#ifndef GINN_LAYER_COMMON_H
#define GINN_LAYER_COMMON_H

#include <algorithm>
#include <iostream>
#include <memory>
#include <numeric>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>

#include <ginn/node/affine.h>
#include <ginn/node/common.h>
#include <ginn/node/inplace.h>
#include <ginn/node/nlnode.h>
#include <ginn/node/weight.h>
#include <ginn/util/lookup.h>
#include <ginn/util/util.h>

#include <ginn/model/lstm.h>

#include <ginn/layer/layer.h>

namespace ginn {

template <typename Scalar, DeviceKind Kind>
using NodePtrs = std::vector<NodePtr<Scalar, Kind>>;

//template <typename Scalar>
//class LstmLayerNode : public LayerNode<NodePtrs<Scalar>(NodePtrs<Scalar>)> {
// public:
//  using State = typename Lstm<Scalar>::State;
//
// private:
//  Real drop_p_ = 0.;
//  Size dim_;
//  bool last_ = false;
//  Lstm<Scalar> lstm_;
//  State h0_; // gotta copy this if not constant
//
// public:
//  LstmLayerNode() = default;
//  LstmLayerNode(DevPtr dev,
//                Size dim,
//                Size xdim,
//                bool last = false,
//                Real drop_p = 0.)
//      : drop_p_(drop_p), dim_(dim), last_(last) {
//    init(dev, dim, xdim);
//  }
//  void init(DevPtr dev, Size dim, Size xdim) {
//    lstm_.init(dev, dim, xdim);
//    h0_ = {Zero(dev, {dim, 1}), Zero(dev, {dim, 1})};
//  }
//
//  NodePtrs<Scalar> run(const NodePtrs<Scalar>& x) override {
//    size_t T = x.size();
//    auto batch_size = Dim(RankView(x.front(), 2), 1);
//    NodePtrs<Scalar> fwd(T), bwd(T);
//    State h_ = std::make_pair(ColBroadcast(h0_.first, batch_size),
//                              ColBroadcast(h0_.second, batch_size));
//
//    auto state = h_;
//    for (size_t t = 0; t < T; t++) {
//      state = lstm_.step(x[t], state);
//      fwd[t] = state.first;
//    }
//
//    if (last_) { fwd = {fwd.back()}; }
//
//    if (this->mode() == Mode::Training and drop_p_ > 0.) {
//      if (fwd.size() == 1) { return {Dropout(fwd.front(), drop_p_)}; }
//      auto mask = Dropout(OnesLike(fwd.front()), drop_p_);
//      for (auto& e : fwd) { e = CwiseProd(mask, e); }
//    }
//
//    return fwd;
//  }
//
//  std::vector<BaseNodePtr> weights_() override {
//    return base_cast(lstm_.weights());
//  }
//
//  LayerPtr<NodePtrs<Scalar>(NodePtrs<Scalar>)> copy(Copy mode) override {
//    auto rval = std::make_shared<LstmLayerNode<Scalar>>();
//    rval->drop_p_ = drop_p_;
//    rval->dim_ = dim_;
//    rval->last_ = last_;
//    rval->lstm_ = lstm_.copy(mode);
//    rval->h0_ = {Zero<Scalar>(lstm_.dev(), {dim_, 1}),
//                 Zero<Scalar>(lstm_.dev(), {dim_, 1})};
//    return rval;
//  }
//};
//
//GINN_MAKE_TEMPLATE_LAYER_FACTORY(LstmLayer);
//
template <typename Scalar, DeviceKind Kind>
class BiLstmLayerNode : public LayerNode<NodePtrs<Scalar, Kind>(NodePtrs<Scalar, Kind>)> {
 public:
  using State = typename Lstm<Scalar, Kind>::State;

 private:
  Real drop_p_ = 0.;
  Size dim_;
  bool last_ = false;
  Lstm<Scalar, Kind> lstm_, rlstm_;
  State h0_; // gotta copy this if not constant

 public:
  BiLstmLayerNode() = default;
  BiLstmLayerNode(DevPtr<Kind> dev,
                  Size dim,
                  Size xdim,
                  bool last = false,
                  Real drop_p = 0.)
      : drop_p_(drop_p), dim_(dim), last_(last) {
    init(dev, dim, xdim);
  }
  void init(DevPtr<Kind> dev, Size dim, Size xdim) {
    lstm_.init(dev, dim, xdim);
    rlstm_.init(dev, dim, xdim);
    h0_ = {Zero<Scalar>(dev, {dim, 1}), Zero<Scalar>(dev, {dim, 1})};
  }

  NodePtrs<Scalar, Kind> run(const NodePtrs<Scalar, Kind>& x) override {
    size_t T = x.size();
    auto batch_size = Dim(RankView(x.front(), 2), 1);
    NodePtrs<Scalar, Kind> fwd(T), bwd(T);
    State h_ = std::make_pair(ColBroadcast(h0_.first, batch_size),
                              ColBroadcast(h0_.second, batch_size));

    auto loop = [&](auto& l, int begin, int end, int incr, auto& res) {
      auto state = h_;
      for (int t = begin; t != end; t += incr) {
        state = l.step(x[t], state);
        res[t] = state.first;
      }
    };

    loop(lstm_, 0, T, 1, fwd);
    loop(rlstm_, T - 1, -1, -1, bwd);

    NodePtrs<Scalar, Kind> res;

    if (last_) {
      res = {Cat(fwd.back(), bwd.front())};
    } else {
      res.resize(T);
      for (size_t t = 0; t < T; t++) { res[t] = Cat(fwd[t], bwd[t]); }
    }

    if (this->mode() == Mode::Training and drop_p_ > 0.) {
      auto mask = Dropout(OnesLike(res.front()), drop_p_);
      for (auto& e : res) { e = CwiseProd(mask, e); }
    }

    return res;
  }

  std::vector<BaseNodePtr> weights_() override {
    return base_cast(lstm_.weights() + rlstm_.weights());
  }

  LayerPtr<NodePtrs<Scalar, Kind>(NodePtrs<Scalar, Kind>)> copy(Copy mode) override {
    auto rval = std::make_shared<BiLstmLayerNode<Scalar, Kind>>();
    rval->drop_p_ = drop_p_;
    rval->dim_ = dim_;
    rval->last_ = last_;
    rval->lstm_ = lstm_.copy(mode);
    rval->rlstm_ = rlstm_.copy(mode);
    rval->h0_ = {Zero<Scalar>(lstm_.dev(), {dim_, 1}),
                 Zero<Scalar>(lstm_.dev(), {dim_, 1})};
    return rval;
  }
};

GINN_MAKE_TEMPLATE2_LAYER_FACTORY(BiLstmLayer);

template <typename T>
T lowercase(const T& x) {
  return x;
}

template <>
char lowercase(const char& x) {
  return ::tolower(x);
}

template <>
std::string lowercase(const std::string& x) {
  auto x_ = x;
  std::transform(x_.begin(), x_.end(), x_.begin(), ::tolower);
  return x_;
}

template <typename Func>
class LookupLayerNode : public LayerNode<Func> {
 public:
  using InputType = typename FunctionTraits<Func>::arg_t;
  using OutputType = typename FunctionTraits<Func>::result_t;
  using Set = std::unordered_set<InputType>;

  static constexpr auto Kind = OutputType::element_type::device_kind;

 private:
  DevPtr<Kind> dev_ = nullptr;
  Size dim_;    // embedding dimension
  Real drop_p_; // word(vector)-dropout rate to randomly replace with unk
  bool lowercased_ = false; // only used for Key == std::string or char

 public:
  LookupTable<InputType, OutputType> table;
  // static_assert(
  //    std::is_convertible_v<NodePtrType, OutputType>,
  //    "LookupLayer expects NodePtrType to be convertible to the output
  //    type!");

  LookupLayerNode() = default;
  LookupLayerNode(DevPtr<Kind> dev, Size dim, Real drop_p = 0., const Set& vocab = {})
      : dev_(dev),
        dim_(dim),
        drop_p_(drop_p),
        table(
            vocab,
            // TODO: Scalar type here needs to be extracted from OutputType
            [=]() { return Weight(dev_, {dim_}); },
            true) {}

  LayerPtr<Func> copy(Copy mode) override {
    auto rval = std::make_shared<LookupLayerNode<Func>>();
    rval->dev_ = this->dev_;
    rval->dim_ = this->dim_;
    rval->drop_p_ = this->drop_p_;
    rval->table = this->table.copy(mode);
    rval->lowercased_ = this->lowercased_;
    return rval;
  }

  OutputType run(const InputType& x) override {
    if (this->mode() == Mode::Training) {
      bool drop = (Real(rand()) / RAND_MAX < drop_p_); // TODO
      return drop ? table.unk() : table[lowercased_ ? lowercase(x) : x];
    }
    return table[lowercased_ ? lowercase(x) : x];
  }

  std::vector<BaseNodePtr> weights_() override {
    return base_cast(table.weights());
  }
};

GINN_MAKE_TEMPLATE_LAYER_FACTORY(LookupLayer);

template <typename Scalar, DeviceKind Kind>
class AffineLayerNode : public LayerNode<NodePtr<Scalar, Kind>(NodePtr<Scalar, Kind>)> {
 public:
  WeightPtr<Scalar, Kind> W, b;
  std::unique_ptr<NonlinOp<Scalar, Kind>> nonlin;

  AffineLayerNode() { init(default_dev<Kind>(), 0, 0); }

  template <typename Nonlin>
  AffineLayerNode(DevPtr<Kind> dev, Nonlin nonlin, Size dim, Size xdim)
      : nonlin(std::make_unique<Nonlin>(nonlin)) {
    init(dev, dim, xdim);
  }

  AffineLayerNode(const AffineLayerNode<Scalar, Kind>& other) {
    W = Weight(*other.W);
    b = Weight(*other.b);
    nonlin = other.nonlin->copy();
  }

  LayerPtr<NodePtr<Scalar, Kind>(NodePtr<Scalar, Kind>)> copy(Copy mode) override {
    auto rval = std::make_shared<AffineLayerNode<Scalar, Kind>>();
    rval->W = W->copy(mode);
    rval->b = b->copy(mode);
    rval->nonlin = nonlin->copy();
    return rval;
  }

  void init(DevPtr<Kind> dev, Size dim, Size xdim) {
    W = Weight(dev, {dim, xdim});
    b = Weight(dev, {dim});
  }

  NodePtr<Scalar, Kind> run(const NodePtr<Scalar, Kind>& x) override {
    return Affine(nonlin->copy(), W, x, b);
  }

  std::vector<BaseNodePtr> weights_() override { return {W, b}; }
};

template <typename Scalar, typename DevicePtr>
auto AffineLayer(DevicePtr dev, Size dim, Size xdim) {
  constexpr auto Kind = DevicePtr::element_type::device_kind;
  return std::make_shared<AffineLayerNode<Scalar, Kind>>(
      std::move(dev), IdentityOp<Scalar, Kind>(), dim, xdim);
}

template <typename Scalar, typename Nonlin, typename DevicePtr>
auto AffineLayer(DevicePtr dev, Size dim, Size xdim) {
  constexpr auto Kind = DevicePtr::element_type::device_kind;
  return std::make_shared<AffineLayerNode<Scalar, Kind>>(std::move(dev), Nonlin(), dim, xdim);
}

template <typename Scalar, typename Nonlin, typename DevicePtr>
auto AffineLayer(DevicePtr dev, Nonlin nonlin, Size dim, Size xdim) {
  constexpr auto Kind = DevicePtr::element_type::device_kind;
  return std::make_shared<AffineLayerNode<Scalar, Kind>>(std::move(dev), nonlin, dim, xdim);
}

template <typename Scalar, DeviceKind Kind>
using NodePtrPair = std::tuple<NodePtr<Scalar, Kind>, NodePtr<Scalar, Kind>>;

template <typename Scalar, DeviceKind Kind>
class CatLayerNode : public LayerNode<NodePtr<Scalar, Kind>(NodePtrPair<Scalar, Kind>)> {
 public:
  CatLayerNode() = default;

  LayerPtr<NodePtr<Scalar, Kind>(NodePtrPair<Scalar, Kind>)> copy(Copy) override {
    return std::make_shared<CatLayerNode>();
  }

  NodePtr<Scalar, Kind> run(const NodePtrPair<Scalar, Kind>& xs) override {
    auto& [a, b] = xs;
    return Cat(a, b);
  }
};

GINN_MAKE_TEMPLATE2_LAYER_FACTORY(CatLayer);

template <typename Scalar, DeviceKind Kind>
class LayerNormLayerNode : public LayerNode<NodePtr<Scalar, Kind>(NodePtr<Scalar, Kind>)> {
 public:
  WeightPtr<Scalar, Kind> gamma = nullptr, beta = nullptr;
  bool inplace_ = false;

  std::vector<BaseNodePtr> weights_() override {
    if (gamma) {
      GINN_ASSERT(beta);
      return {gamma, beta};
    }
    GINN_ASSERT(not beta);
    return {};
  }

  NodePtr<Scalar, Kind> run(const NodePtr<Scalar, Kind>& x) override {
    NodePtr<Scalar, Kind> ln;
    if (inplace_) {
      ln = InPlaceLayerNorm(x);
    } else {
      ln = LayerNorm(x);
    }
    if (gamma) {
      GINN_ASSERT(beta);
      return CwiseProdAdd(ln, gamma, beta, 1.);
    } else {
      GINN_ASSERT(not beta);
      return ln;
    }
  }

  void init(DevPtr<Kind> dev, Size dim) {
    gamma = Weight(dev, {dim});
    beta = Weight(dev, {dim});
  }

  LayerNormLayerNode() = default;
  LayerNormLayerNode(DevPtr<Kind> dev, Size dim, bool inplace = false)
      : inplace_(inplace) {
    init(dev, dim);
  }
  LayerNormLayerNode(const LayerNormLayerNode& other) {
    if (other.gamma) { gamma = Weight(*other.gamma); }
    if (other.beta) { beta = Weight(*other.beta); }
  }

  LayerPtr<NodePtr<Scalar, Kind>(NodePtr<Scalar, Kind>)> copy(Copy mode) override {
    auto rval = std::make_shared<LayerNormLayerNode<Scalar, Kind>>();
    if (gamma) { rval->gamma = gamma->copy(mode); }
    if (beta) { rval->beta = beta->copy(mode); }
    return rval;
  }
};

GINN_MAKE_TEMPLATE2_LAYER_FACTORY(LayerNormLayer);

template <typename Scalar, DeviceKind Kind>
class DropoutLayerNode : public LayerNode<NodePtr<Scalar, Kind>(NodePtr<Scalar, Kind>)> {
 private:
  Real drop_p_ = 0;
  bool inplace_ = false;

 public:
  NodePtr<Scalar, Kind> run(const NodePtr<Scalar, Kind>& x) override {
    if (this->mode() == Mode::Training) {
      if (inplace_) { return InPlaceDropout(x, drop_p_); }
      return Dropout(x, drop_p_);
    }
    return x;
  }

  DropoutLayerNode() = default;
  DropoutLayerNode(Real drop_p, bool inplace = false)
      : drop_p_(drop_p), inplace_(inplace) {}
  DropoutLayerNode(const DropoutLayerNode& other) = default;

  LayerPtr<NodePtr<Scalar, Kind>(NodePtr<Scalar, Kind>)> copy(Copy /*mode*/) override {
    return std::make_shared<DropoutLayerNode<Scalar, Kind>>(drop_p_, inplace_);
  }
};

GINN_MAKE_TEMPLATE2_LAYER_FACTORY(DropoutLayer);

} // namespace ginn

#endif

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

#ifndef GINN_NODE_COMMON_H
#define GINN_NODE_COMMON_H

#include <ginn/node.h>
#include <ginn/node/data.h>
#include <ginn/util/traits.h>

namespace ginn {

template <typename Scalar, DeviceKind Kind>
class AddScalarNode : public BaseDataNode<Scalar, Kind> {
  static_assert(not std::is_same_v<Scalar, bool>);
  static_assert(ginn::is_arithmetic_v<Scalar>);

 protected:
  NodePtr<Scalar, Kind> in_;
  Raw<Scalar> val_;

  void forward_() override {
    value().resize(in_->value().shape());
    value() = in_->value().t() + val_;
  }

  void backward_() override {
    if (in_->has_grad()) { in_->grad() += grad().t(); }
  }

 public:
  using BaseDataNode<Scalar, Kind>::value;
  using BaseDataNode<Scalar, Kind>::grad;

  template <typename RightScalar>
  AddScalarNode(const NodePtr<Scalar, Kind>& a, RightScalar b)
      : BaseDataNode<Scalar, Kind>(a), in_(a), val_(Raw<Scalar>(b)) {}

  std::string name() const override { return "AddScalar"; }
};

GINN_MAKE_SCALAR_FORWARDING_FACTORY(AddScalar);

// To be used when scalar is on the left e.g. 1 - x, otherwise we can use
// AddScalar instead since doing x - 1 == x + (-(-1)) is cheap, no negation
// of a node type, no temporary nodes.
template <typename Scalar, DeviceKind Kind>
class SubtractScalarNode : public BaseDataNode<Scalar, Kind> {
  static_assert(not std::is_same_v<Scalar, bool>);
  static_assert(ginn::is_arithmetic_v<Scalar>);

 protected:
  NodePtr<Scalar, Kind> in_;
  Raw<Scalar> val_;

  void forward_() override {
    value().resize(in_->value().shape());
    value() = val_ - in_->value().t();
  }

  void backward_() override {
    if (in_->has_grad()) { in_->grad() -= grad().t(); }
  }

 public:
  using BaseDataNode<Scalar, Kind>::value;
  using BaseDataNode<Scalar, Kind>::grad;

  template <typename LeftScalar>
  SubtractScalarNode(LeftScalar a, const NodePtr<Scalar, Kind>& b)
      : BaseDataNode<Scalar, Kind>(b), in_(b), val_(Raw<Scalar>(a)) {}

  std::string name() const override { return "SubtractScalar"; }
};

template <typename LeftScalar,
          typename NodePtr,
          typename = std::enable_if_t<ginn::is_node_ptr_v<NodePtr>>>
auto SubtractScalar(LeftScalar a, NodePtr b) {
  using Scalar = typename NodePtr::element_type::Scalar;
  constexpr auto Kind = NodePtr::element_type::device_kind;
  return make_ptr<SubtractScalarNode<Scalar, Kind>>(a, std::move(b));
}

template <typename Scalar, DeviceKind Kind>
class AddNode : public BaseDataNode<Scalar, Kind> {
 protected:
  std::vector<NodePtr<Scalar, Kind>> ins_;

  // Helper to add N input tensors like:
  // in(0)->value().t() + ... + in(N-1)->value().t().
  // Eigen benefits from compile time unrolling of this sum.
  template <size_t... N>
  auto add_helper(size_t i, std::integer_sequence<size_t, N...>) {
    return (ins_[i + N]->value().t() + ...);
  }

  template <size_t N>
  auto add_helper(size_t i) {
    return add_helper(i, std::make_integer_sequence<size_t, N>());
  }

  void forward_() override {
    value().resize(ins_[0]->value().shape());

    auto compute = [&](const auto& rhs, bool accumulate) {
      accumulate ? (value() += rhs) : (value() = rhs);
    };

    for (size_t i = 0; i < ins_.size(); i += 4) {
      size_t remaining = std::min(ins_.size() - i, (size_t)4);
      if (remaining == 0) { remaining = 4; }
      switch (remaining) {
      case 1: compute(ins_[i]->value().t(), i > 0); break;
      case 2: compute(add_helper<2>(i), i > 0); break;
      case 3: compute(add_helper<3>(i), i > 0); break;
      case 4: compute(add_helper<4>(i), i > 0); break;
      }
    }
  }

  void backward_() override {
    for (size_t i = 0; i < ins_.size(); i++) {
      if (ins_[i]->has_grad()) { ins_[i]->grad() += grad().t(); }
    }
  }

 public:
  using Base = BaseDataNode<Scalar, Kind>;
  using Base::grad;
  using Base::value;

  AddNode(const std::vector<NodePtr<Scalar, Kind>>& ins)
      : Base(ins), ins_(ins) {}

  template <typename... Args>
  AddNode(const NodePtr<Scalar, Kind>& in, const Args&... args)
      : AddNode(std::vector<NodePtr<Scalar, Kind>>{in, args...}) {}

  void set_ins(const std::vector<BaseNodePtr>& ins) override {
    BaseNode::ins_ = ins;
    ins_ = derived_cast<Node<Scalar, Kind>>(ins);
  }

  std::string name() const override { return "Add"; }
}; // namespace ginn

GINN_MAKE_SCALAR_FORWARDING_FACTORY(Add);

template <typename Scalar, DeviceKind Kind>
class SubtractNode : public BaseDataNode<Scalar, Kind> {
 private:
  NodePtr<Scalar, Kind> left_, right_;

  void forward_() override {
    value().resize(left_->shape());
    value() = left_->value().t() - right_->value().t();
  }

  void backward_() override {
    if (left_->has_grad()) { left_->grad() += grad().t(); }
    if (right_->has_grad()) { right_->grad() -= grad().t(); }
  }

 public:
  using BaseDataNode<Scalar, Kind>::value;
  using BaseDataNode<Scalar, Kind>::grad;

  SubtractNode(const NodePtr<Scalar, Kind>& a, const NodePtr<Scalar, Kind>& b)
      : BaseDataNode<Scalar, Kind>({a, b}), left_(a), right_(b) {}

  std::string name() const override { return "Subtract"; }
};

GINN_MAKE_SCALAR_FORWARDING_FACTORY(Subtract);

template <typename Scalar, DeviceKind Kind>
class ProdScalarNode : public BaseDataNode<Scalar, Kind> {
 protected:
  NodePtr<Scalar, Kind> in_;
  Raw<Scalar> val_;

  void forward_() override {
    value().resize(in_->value().shape());
    value() = in_->value().t() * val_;
  }

  void backward_() override {
    if (in_->has_grad()) { in_->grad() += grad().t() * val_; }
  }

 public:
  using BaseDataNode<Scalar, Kind>::value;
  using BaseDataNode<Scalar, Kind>::grad;

  template <typename RightScalar>
  ProdScalarNode(const NodePtr<Scalar, Kind>& a, RightScalar b)
      : BaseDataNode<Scalar, Kind>(a), in_(a), val_(Raw<Scalar>(b)) {}

  std::string name() const override { return "ProdScalar"; }
};

GINN_MAKE_SCALAR_FORWARDING_FACTORY(ProdScalar);

template <typename Scalar, DeviceKind Kind>
class CwiseProdNode : public BaseDataNode<Scalar, Kind> {
 protected:
  NodePtr<Scalar, Kind> a_, b_;

  void forward_() override {
    value().resize(a_->value().shape());
    value() = a_->value().t() * b_->value().t();
  }

  void backward_() override {
    if (a_->has_grad()) { a_->grad() += grad().t() * b_->value().t(); }
    if (b_->has_grad()) { b_->grad() += grad().t() * a_->value().t(); }
  }

 public:
  using BaseDataNode<Scalar, Kind>::value;
  using BaseDataNode<Scalar, Kind>::grad;

  CwiseProdNode(const NodePtr<Scalar, Kind>& a, const NodePtr<Scalar, Kind>& b)
      : BaseDataNode<Scalar, Kind>({a, b}), a_(a), b_(b) {}

  std::string name() const override { return "CwiseProd"; }
};

GINN_MAKE_SCALAR_FORWARDING_FACTORY(CwiseProd);

template <typename Scalar, DeviceKind Kind>
class CwiseProdAddNode : public BaseDataNode<Scalar, Kind> {
 private:
  NodePtr<Scalar, Kind> a_, b_, c_;
  bool broadcast_;
  Raw<Scalar> multiplier_bias_{0};

  void forward_() override {
    const auto s0 = a_->shape(), s1 = b_->shape(), s2 = c_->shape();
    if (s0 == s1 and s1 == s2) {
      broadcast_ = false;
    } else if (s1.size() == 1 and s2.size() == 1) {
      broadcast_ = true;
      GINN_ASSERT(s0[0] == s1[0] and s1[0] == s2[0],
                  "Unexpected shapes for CwiseProdAdd!");
    } else {
      GINN_THROW("Unexpected shapes for CwiseProdAdd!");
    }

    value().resize(s0);
    auto a_t = a_->value().t();
    auto b_t = b_->value().t();
    auto c_t = c_->value().t();

    if (not broadcast_) {
      value() = a_t * (b_t + multiplier_bias_) + c_t;
    } else {
      auto cols = a_->shape2()[1];
      value() = a_t * (b_t + multiplier_bias_).broadcast(Index<2>{1, cols}) +
                c_t.broadcast(Index<2>{1, cols});
    }
  }

  void backward_() override {
    auto a_t = a_->value().t();
    auto b_t = b_->value().t();

    if (not broadcast_) {
      if (a_->has_grad()) {
        a_->grad() += grad().t() * (b_t + multiplier_bias_);
      }
      if (b_->has_grad()) { b_->grad() += grad().t() * a_t; }
      if (c_->has_grad()) { c_->grad() += grad().t(); }
    } else {
      if (a_->has_grad()) {
        const auto cols = a_->shape2()[1];
        a_->grad() +=
            grad().t() * (b_t + multiplier_bias_).broadcast(Index<2>{1, cols});
      }
      if (b_->has_grad()) { b_->grad() += (grad().t() * a_t).sum(Index<1>{1}); }
      if (c_->has_grad()) { c_->grad() += grad().t().sum(Index<1>{1}); }
    }
  }

 public:
  using BaseDataNode<Scalar, Kind>::value;
  using BaseDataNode<Scalar, Kind>::grad;

  template <typename BiasScalar = Raw<Scalar>>
  CwiseProdAddNode(const NodePtr<Scalar, Kind>& a,
                   const NodePtr<Scalar, Kind>& b,
                   const NodePtr<Scalar, Kind>& c,
                   BiasScalar multiplier_bias = BiasScalar(0))
      : BaseDataNode<Scalar, Kind>({a, b, c}),
        a_(a),
        b_(b),
        c_(c),
        multiplier_bias_(Raw<Scalar>(multiplier_bias)) {}

  std::string name() const override { return "CwiseProdAdd"; }
};

GINN_MAKE_SCALAR_FORWARDING_FACTORY(CwiseProdAdd);

template <typename Scalar, DeviceKind Kind>
class CwiseMaxNode : public BaseDataNode<Scalar, Kind> {
 private:
  std::vector<NodePtr<Scalar, Kind>> ins_;

  void forward_() override {
    value().resize(ins_[0]->value().shape());
    value() = ins_[0]->value().t();
    for (size_t i = 1; i < ins_.size(); i++) {
      value() = value().t().cwiseMax(ins_[i]->value().t());
    }
  }

  void backward_() override {
    for (size_t i = 0; i < ins_.size(); i++) {
      if (ins_[i]->has_grad()) {
        ins_[i]->grad() +=
            grad().t() *
            (ins_[i]->value().t() == value().t()).template cast<Raw<Scalar>>();
      }
    }
  }

 public:
  using BaseDataNode<Scalar, Kind>::value;
  using BaseDataNode<Scalar, Kind>::grad;

  CwiseMaxNode(const std::vector<NodePtr<Scalar, Kind>>& ins)
      : BaseDataNode<Scalar, Kind>(ins), ins_(ins) {}
  template <typename... Args>
  CwiseMaxNode(const NodePtr<Scalar, Kind>& in, const Args&... args)
      : BaseDataNode<Scalar, Kind>(
            std::vector<NodePtr<Scalar, Kind>>{in, args...}),
        ins_(std::vector<NodePtr<Scalar, Kind>>{in, args...}) {}

  std::string name() const override { return "CwiseMax"; }
};

GINN_MAKE_SCALAR_FORWARDING_FACTORY(CwiseMax);

// TODO: explicit seed?
template <typename Scalar, DeviceKind Kind>
class DropoutNode : public BaseDataNode<Scalar, Kind> {
  static_assert(ginn::is_floating_point_v<Scalar>,
                "Dropout scalar needs to be floating point because of "
                "inference time rescaling!");

 protected:
  NodePtr<Scalar, Kind> in_;
  Real p_;
  Tensor<bool, Kind> mask_;
  using RawScalar = Raw<Scalar>;

  void forward_() override {
    value().resize(in_->value().shape());
    if (p_ == 1.) {
      value().set_zero();
    } else {
      mask_.resize(in_->shape());
      mask_ = (mask_.t().template cast<Real>().random() >= p_);
      RawScalar tmp(1. / (1. - p_));
      // TODO: should I benchmark this against using .select()?
      value() = in_->value().t() * mask_.t().template cast<RawScalar>() * tmp;
    }
  }

  void backward_() override {
    if (in_->has_grad() and p_ < 1.) {
      RawScalar tmp(1. / (1. - p_));
      in_->grad() += grad().t() * mask_.t().template cast<RawScalar>() * tmp;
    }
  }

 public:
  using BaseDataNode<Scalar, Kind>::value;
  using BaseDataNode<Scalar, Kind>::grad;

  std::string name() const override { return "Dropout"; }

  DropoutNode(const NodePtr<Scalar, Kind>& in, Real p)
      : BaseDataNode<Scalar, Kind>(in), in_(in), p_(p), mask_(in->dev()) {
    GINN_ASSERT(p_ >= 0 and p_ <= 1, "Dropout probability is not in [0, 1]!");
  }
};

GINN_MAKE_SCALAR_FORWARDING_FACTORY(Dropout);

//  Arithmetic operator overloads

template <typename Left,
          typename Right,
          typename = std::enable_if_t<ginn::is_node_ptr_v<Left> or
                                      ginn::is_node_ptr_v<Right>>>
auto operator+(const Left& a, const Right& b) {
  if constexpr (ginn::is_node_ptr_v<Left>) {
    if constexpr (ginn::is_node_ptr_v<Right>) {
      return Add(a, b);
    } else {
      return AddScalar(a, b);
    }
  } else {
    return AddScalar(b, a);
  }
}

template <typename Left,
          typename Right,
          typename = std::enable_if_t<ginn::is_node_ptr_v<Left> or
                                      ginn::is_node_ptr_v<Right>>>
auto operator-(const Left& a, const Right& b) {
  if constexpr (ginn::is_node_ptr_v<Left>) {
    if constexpr (ginn::is_node_ptr_v<Right>) {
      return Subtract(a, b);
    } else {
      return AddScalar(a, -b);
    }
  } else {
    return SubtractScalar(a, b);
  }
}

template <typename NodePtr,
          typename = std::enable_if_t<ginn::is_node_ptr_v<NodePtr>>>
auto operator-(const NodePtr& in) {
  // return in * Scalar(-1); // do these differ in timings?
  return 0 - in;
}

template <typename Left,
          typename Right,
          typename = std::enable_if_t<ginn::is_node_ptr_v<Left> xor
                                      ginn::is_node_ptr_v<Right>>>
auto operator*(const Left& a, const Right& b) {
  if constexpr (ginn::is_node_ptr_v<Left>) {
    return ProdScalar(a, b);
  } else {
    return ProdScalar(b, a);
  }
}

} // namespace ginn
#endif

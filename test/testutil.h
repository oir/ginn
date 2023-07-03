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

#ifndef GINN_TESTUTIL_H
#define GINN_TESTUTIL_H

#include <catch2/catch.hpp>
#include <cppitertools/zip.hpp>

#include <ginn/node/common.h>
#include <ginn/node/reduce.h>
#include <ginn/node/weight.h>
#include <ginn/util/stdcontainerio.h>
#include <ginn/util/tensorio.h>
#include <ginn/util/traits.h>

namespace ginn {

// Approximate tensor matcher to be able to run:
//   CHECK(tensor1 == Close(tensor2));
//   in Catch, when checking approximate equality of float tensors.

template <typename Scalar, DeviceKind Kind>
bool equals(const Tensor<Scalar, Kind>& left,
            const Tensor<Scalar, Kind>& right,
            const Catch::Detail::Approx& approx) {
  if (left.shape() != right.shape()) {
    return false;
  } else if constexpr (Kind != CPU) {
    return equals(left.copy_to(cpu()), right.copy_to(cpu()), approx);
  } else {
    for (auto [a, b] : iter::zip(left, right)) {
      if (b != approx(a)) { return false; }
    }
    return true;
  }
}

bool equals(const std::vector<Real>& left,
            const std::vector<Real>& right,
            const Catch::Detail::Approx& approx) {
  if (left.size() != right.size()) { return false; }
  for (auto [a, b] : iter::zip(left, right)) {
    if (b != approx(a)) { return false; }
  }
  return true;
}

// NOTE: the following is what I used to do for compare_devices
// auto check_close(Real a, Real b, Real eps) {
//  using namespace Catch::Matchers;
//  CHECK_THAT(a,
//             WithinRel(b, eps) or
//                 (WithinAbs(0., 2e-3) and WithinAbs(b, 0.1 * eps)));
//}

template <typename T>
class Close {
 private:
  const T& val_;
  mutable Catch::Detail::Approx approx_ = Catch::Detail::Approx::custom();

 public:
  explicit Close(const T& val) : val_(val) {}

  auto& margin(double m) {
    approx_.margin(m);
    return *this;
  }
  auto& epsilon(double eps) {
    approx_.epsilon(eps);
    return *this;
  }
  auto& scale(double s) {
    approx_.scale(s);
    return *this;
  }

  friend bool operator==(const T& l, const Close& r) {
    return equals(l, r.val_, r.approx_);
  }
  friend bool operator==(const Close& l, const T& r) { return r == l; }
  friend bool operator!=(const T& l, Close const& r) { return not(l == r); }
  friend bool operator!=(const Close& l, const T& r) { return not(r == l); }

  friend std::ostream& operator<<(std::ostream& o, const Close<T>& rhs) {
    o << rhs.val_;
    return o;
  }
};

// Compute numeric grad for gradient checks, using finite differences
template <typename Expr, typename Weight, typename Mask>
inline Tensor<Real> numeric_grad(Expr e, Weight w, Mask mask, Real eps = 1e-4) {
  auto s = Sum(CwiseProd(mask, e));

  auto g = Graph(s);
  Tensor<Real> rval(w->dev(), w->shape());

  for (uint i = 0; i < w->size(); i++) {
    auto value = w->value().m();
    Real tmp = value(i);
    value(i) = tmp + eps;
    g.reset_forwarded();
    g.forward();
    Real s_plus = e->value().m().cwiseProduct(mask->value().m()).sum();

    value(i) = tmp - eps;
    g.reset_forwarded();
    g.forward();
    Real s_minus = e->value().m().cwiseProduct(mask->value().m()).sum();

    rval.v()(i) = (s_plus - s_minus) / (2 * eps);
    value(i) = tmp;
  }

  return rval;
}

// Compute analytic grad for gradient checks, by calling backward()
template <typename Expr, typename Weight, typename Mask>
inline Tensor<Real> analytic_grad(Expr e, Weight w, Mask mask) {
  auto s = Sum(CwiseProd(mask, e));

  auto g = Graph(s);
  g.reset_forwarded(); // gradcheck reuses expressions
  g.forward();
  g.reset_grad();
  g.backward(1.);

  return w->grad();
}

template <typename NodeContainer>
inline void check_grad(NodePtr<Real> e,
                       const NodeContainer& ins,
                       bool randomize_inputs = false,
                       Real eps = 1e-4,
                       Real delta = 1e-4) {
  static_assert(ginn::is_node_ptr_v<typename NodeContainer::value_type>,
                "ins should contain derived Node pointer types!");

  if (randomize_inputs) {
    for (BaseNodePtr w : ins) {
      if (auto w_ = dynamic_ptr_cast<BaseDataNode<>>(w)) {
        w_->value().set_random();
      } else if (auto w_ = dynamic_ptr_cast<WeightNode<>>(w)) {
        w_->value().set_random();
      }
    }
  }

  e = e + e; // to make sure gradient accumulates over input repetition
  auto g = Graph(e);
  g.reset_forwarded();
  g.forward(); // to init all shapes

  for (BaseNodePtr w : ins) {
    if ((dynamic_ptr_cast<BaseDataNode<>>(w) or
         dynamic_ptr_cast<WeightNode<>>(w)) and
        w->has_grad()) {
      w->reset_grad();
      auto wr = dynamic_ptr_cast<Node<Real>>(w);
      auto mask = Random(e->dev(), e->value().shape());
      mask->set_has_grad(false);
      auto ng = numeric_grad(e, wr, mask, delta);
      auto ag = analytic_grad(e, wr, mask);
      CHECK(ag == Close(ng).scale(eps));
    }
  }
}

inline void check_grad(const NodePtr<Real>& e,
                       const std::initializer_list<BaseNodePtr>& ins,
                       bool randomize_inputs = false,
                       Real eps = 1e-4,
                       Real delta = 1e-4) {
  check_grad(e, std::vector<BaseNodePtr>(ins), randomize_inputs, eps, delta);
}

#ifdef GINN_ENABLE_GPU
template <typename... Args>
auto to_gpu(Args&&... args) {
  return std::make_tuple(args->copy_to(gpu())...);
}
#endif

//// TODO: consider putting this in ginn/util/
//// loop over values with heterogeneous types
//// useful for applying some logic to a list of differently typed values
// template <typename... Args, typename F>
// void for_each(Args&&... args, F f) {
//  (f(std::forward<Args>(args)), ...);
//}
} // namespace ginn

#endif

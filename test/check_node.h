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

#ifndef GINN_CHECK_NODE_H
#define GINN_CHECK_NODE_H

#include <cppitertools/zip.hpp>

#include <ginn/node.h>

#include "testutil.h"

using namespace ginn; // This header is not part of the library, should be fine

#ifdef GINN_ENABLE_GPU // if gpu is enabled, we run cuda tests

auto check_close(Real a, Real b, Real eps) {
  using namespace Catch::Matchers;
  CHECK_THAT(a,
             WithinRel(b, eps) or
                 (WithinAbs(0., 2e-3) and WithinAbs(b, 0.1 * eps)));
}

template <typename CpuNodePtr, typename GpuNodePtr>
void compare_devices(const CpuNodePtr& cpu_e,
                     const std::initializer_list<BaseNodePtr>& cpu_ins,
                     const GpuNodePtr& gpu_e,
                     const std::initializer_list<BaseNodePtr>& gpu_ins,
                     Real eps = 1e-4) {
  static_assert(ginn::is_node_ptr_v<CpuNodePtr>);
  static_assert(ginn::is_node_ptr_v<GpuNodePtr>);
  static_assert(std::is_same_v<typename CpuNodePtr::element_type::Scalar,
                               typename GpuNodePtr::element_type::Scalar>);
  GINN_ASSERT(cpu_ins.size() == gpu_ins.size());

  Vector<Real> cpu_val, gpu_val;
  std::vector<Vector<Real>> cpu_grads, gpu_grads;

  auto fwd = [&](auto& expr, auto& val) {
    auto e = expr + expr; // "+" ensures multiple paths for backprop, good
                          // for testing accumulated gradients
    auto g = Graph(e);
    g.forward();

    val = e->value().maybe_copy_to(cpu()).template cast<Real>().v();
    return g;
  };

  auto cpu_g = fwd(cpu_e, cpu_val);
  auto gpu_g = fwd(gpu_e, gpu_val);

  for (auto&& [a, b] : iter::zip(cpu_val, gpu_val)) { check_close(a, b, eps); }

  bool has_grad = cpu_e->has_grad() and gpu_e->has_grad();
  if (has_grad) {
    using Scalar = typename CpuNodePtr::element_type::Scalar;
    cpu_g.reset_grad(), gpu_g.reset_grad();
    Tensor<Real> grad(cpu(), cpu_e->grad().shape());
    grad.set_random();
    cpu_e->grad() = grad.cast<Scalar>();
    gpu_e->grad() = cpu_e->grad();

    auto bwd = [&](auto& g, auto& e, auto& grads, auto& ins) {
      g.backward();
      const static auto Kind =
          std::decay_t<decltype(e)>::element_type::device_kind;
      for (auto& in : ins) {
        if (auto in_ = dynamic_ptr_cast<DataNode<Real, Kind>>(in)) {
          grads.push_back(in_->grad().maybe_copy_to(cpu()).v());
        } else if (auto in_ = dynamic_ptr_cast<WeightNode<Real, Kind>>(in)) {
          grads.push_back(in_->grad().maybe_copy_to(cpu()).v());
        } else if (auto in_ = dynamic_ptr_cast<DataNode<Half, Kind>>(in)) {
          grads.push_back(
              in_->grad().maybe_copy_to(cpu()).template cast<Real>().v());
        } else if (auto in_ = dynamic_ptr_cast<WeightNode<Half, Kind>>(in)) {
          grads.push_back(
              in_->grad().maybe_copy_to(cpu()).template cast<Real>().v());
        }
      }
    };

    bwd(cpu_g, cpu_e, cpu_grads, cpu_ins);
    bwd(gpu_g, gpu_e, gpu_grads, gpu_ins);

    for (auto&& [cpu_grad, gpu_grad] : iter::zip(cpu_grads, gpu_grads)) {
      for (auto&& [a, b] : iter::zip(cpu_grad, gpu_grad)) {
        check_close(a, b, eps);
      }
    }
  }
}

//// Check if CPU and GPU forward & backward operations result in same numbers
// template <typename NodeFunc>
// void check_expr(NodeFunc expr,
//                 std::vector<BaseNodePtr> ins,
//                 bool randomize_inputs = false,
//                 Real eps = 1e-4) {
//   static_assert(ginn::is_node_ptr_v<std::invoke_result_t<NodeFunc>>);
//   using Scalar = typename
//   std::invoke_result_t<NodeFunc>::element_type::Scalar;
//   std::unordered_map<DeviceKind, Vector<Real>> values;
//   std::unordered_map<DeviceKind, std::vector<Vector<Real>>> grads;
//   Tensor<Real> cpu_grad;
//   for (auto dev : std::vector<DevPtr>{cpu(), gpu()}) {
//     for (auto& x : ins) {
//       if (auto x_ = dynamic_ptr_cast<DataNode<Real>>(x)) {
//         x_->move_to(dev);
//         if (randomize_inputs and dev == cpu()) { x_->set_random(); }
//       } else if (auto x_ = dynamic_ptr_cast<DataNode<Int>>(x)) {
//         x_->move_to(dev);
//       } else if (auto x_ = dynamic_ptr_cast<DataNode<Half>>(x)) {
//         x_->move_to(dev);
//         if (randomize_inputs and dev == cpu()) { x_->set_random(); }
//       } else if (auto x_ = dynamic_ptr_cast<DataNode<bool>>(x)) {
//         x_->move_to(dev);
//       } else if (auto x_ = dynamic_ptr_cast<WeightNode<Real>>(x)) {
//         x_->move_to(dev);
//         if (randomize_inputs and dev == cpu()) { x_->set_random(); }
//       } else if (auto x_ = dynamic_ptr_cast<WeightNode<Half>>(x)) {
//         x_->move_to(dev);
//         if (randomize_inputs and dev == cpu()) { x_->set_random(); }
//       }
//     }
//     bool has_grad = expr()->has_grad();
//     auto e = expr() + expr(); // "+" ensures multiple paths for backprop,
//     good
//                               // for testing accumulated gradients
//
//     auto g = Graph(e);
//     g.reset_forwarded();
//     g.forward();
//
//     values[dev->kind()] =
//         e->value().maybe_copy_to(cpu()).template cast<Real>().v();
//
//     if constexpr (ginn::is_floating_point_v<Scalar>) {
//       if (has_grad) {
//         g.reset_grad();
//         if (dev->kind() == CPU) {
//           Tensor<Real> grad(cpu(), e->grad().shape());
//           grad.set_random();
//           e->grad() = grad.cast<Scalar>();
//           cpu_grad = grad;
//         } else {
//           e->grad().lhs() += Tensor<Real>(gpu(),
//           cpu_grad).t().cast<Scalar>();
//         }
//         g.backward();
//
//         for (auto& in : ins) {
//           if (auto in_ = dynamic_ptr_cast<DataNode<Real>>(in)) {
//             Tensor<Real> grad = in_->grad();
//             grad.move_to(cpu());
//             grads[dev->kind()].push_back(grad.v());
//           } else if (auto in_ = dynamic_ptr_cast<WeightNode<Real>>(in)) {
//             Tensor<Real> grad = in_->grad();
//             grad.move_to(cpu());
//             grads[dev->kind()].push_back(grad.v());
//           } else if (auto in_ = dynamic_ptr_cast<DataNode<Half>>(in)) {
//             Tensor<Half> grad = in_->grad();
//             grad.move_to(cpu());
//             grads[dev->kind()].push_back(grad.cast<Real>().v());
//           } else if (auto in_ = dynamic_ptr_cast<WeightNode<Half>>(in)) {
//             Tensor<Half> grad = in_->grad();
//             grad.move_to(cpu());
//             grads[dev->kind()].push_back(grad.cast<Real>().v());
//           }
//         }
//       }
//     }
//   }
//
//   using namespace Catch::Matchers;
//   for (Size i = 0; i < values[CPU].size(); i++) {
//     CHECK_THAT(
//         values[GPU][i],
//         WithinRel(values[CPU][i], eps) or
//             (WithinAbs(0., 2e-3) and WithinAbs(values[CPU][i], 0.1 * eps)));
//   }
//   if constexpr (ginn::is_floating_point_v<Scalar>) {
//     for (size_t i = 0; i < grads[CPU].size(); i++) {
//       for (Size j = 0; j < grads[CPU][i].size(); j++) {
//         CHECK_THAT(grads[GPU][i][j],
//                    WithinRel(grads[CPU][i][j], eps) or
//                        (WithinAbs(0., 2e-3) and
//                         WithinAbs(grads[CPU][i][j], 0.1 * eps)));
//       }
//     }
//   }
// }

#else // if gpu is not enabled, we do gradchecks

template <typename NodeFunc>
void check_expr(NodeFunc f_e,
                const std::vector<BaseNodePtr>& ins,
                bool randomize_inputs = false,
                Real eps = 1e-4) {
  using Scalar = typename std::invoke_result_t<NodeFunc>::element_type::Scalar;
  if constexpr (std::is_same_v<Scalar, Real>) {
    check_grad(f_e, ins, randomize_inputs, eps);
  } else {
    // skip gradcheck if Scalar type is not Real
  }
}

template <typename NodeFunc>
void check_expr(NodeFunc e,
                const std::initializer_list<BaseNodePtr>& ins,
                bool randomize_inputs = false,
                Real eps = 1e-4) {
  check_expr(e, std::vector<BaseNodePtr>(ins), randomize_inputs, eps);
}

#endif

// Helper macro for quick one liner expression generators
#define CHECK_(e, args...) check_expr([&]() { return e; }, args)

template <typename Left, typename Right>
void check(Left e, Right f, Real eps = 1e-6) {
  static_assert(ginn::is_node_ptr_v<Left>);
  static_assert(ginn::is_node_ptr_v<Right>);
  REQUIRE(std::is_same_v<typename Left::element_type::Scalar,
                         typename Right::element_type::Scalar>);
  Graph(e).reset_forwarded().forward();
  Graph(f).reset_forwarded().forward();
  REQUIRE(e->value().shape() == f->value().shape());
  for (Size i = 0; i < e->value().size(); i++) {
    CHECK(e->value().v()(i) == Approx(f->value().v()(i)).epsilon(eps));
  }
}

#endif // GINN_CHECK_NODE_H

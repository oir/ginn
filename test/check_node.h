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

template <typename CpuNodePtr,
          typename CpuIn,
          typename GpuNodePtr,
          typename GpuIn>
void compare_devices(const CpuNodePtr& cpu_e,
                     const std::initializer_list<CpuIn>& cpu_ins,
                     const GpuNodePtr& gpu_e,
                     const std::initializer_list<GpuIn>& gpu_ins,
                     Real eps = 1e-4) {
  static_assert(ginn::is_node_ptr_v<CpuNodePtr>);
  static_assert(ginn::is_node_ptr_v<GpuNodePtr>);
  static_assert(ginn::is_node_ptr_v<CpuIn>);
  static_assert(ginn::is_node_ptr_v<GpuIn>);
  static_assert(std::is_same_v<typename CpuNodePtr::element_type::Scalar,
                               typename GpuNodePtr::element_type::Scalar>);
  static_assert(std::is_same_v<typename CpuIn::element_type::Scalar,
                               typename GpuIn::element_type::Scalar>);
  GINN_ASSERT(cpu_ins.size() == gpu_ins.size());

  std::vector<Real> cpu_val, gpu_val;
  std::vector<std::vector<Real>> cpu_grads, gpu_grads;

  auto fwd = [&](auto& expr, auto& val) {
    auto e = expr + expr; // "+" ensures multiple paths for backprop, good
                          // for testing accumulated gradients
    auto g = Graph(e);
    g.forward();

    val = e->value().real().vector();
    return g;
  };

  auto cpu_g = fwd(cpu_e, cpu_val);
  auto gpu_g = fwd(gpu_e, gpu_val);

  CHECK(cpu_val == Close(gpu_val).epsilon(eps));

  bool has_grad = cpu_e->has_grad() and gpu_e->has_grad();
  if (has_grad) {
    using Scalar = typename CpuNodePtr::element_type::Scalar;
    cpu_g.reset_grad(), gpu_g.reset_grad();
    Tensor<Real> grad(cpu(), cpu_e->grad().shape());
    grad.set_random();

    cpu_e->grad() = grad.cast<Scalar>();
    gpu_e->grad() = cpu_e->grad();

    auto bwd = [&](auto& g, auto& grads, auto& ins) {
      g.backward_();
      for (auto& in : ins) {
        GINN_ASSERT(in->ins().empty());
        grads.push_back(in->grad().real().vector());
      }
    };

    bwd(cpu_g, cpu_grads, cpu_ins);
    bwd(gpu_g, gpu_grads, gpu_ins);

    for (auto&& [cpu_grad, gpu_grad] : iter::zip(cpu_grads, gpu_grads)) {
      CHECK(cpu_grad == Close(gpu_grad).epsilon(eps));
    }
  }
}

#endif

template <typename Left, typename Right>
void check(Left e, Right f, Real eps = 1e-6) {
  static_assert(ginn::is_node_ptr_v<Left>);
  static_assert(ginn::is_node_ptr_v<Right>);
  REQUIRE(std::is_same_v<typename Left::element_type::Scalar,
                         typename Right::element_type::Scalar>);
  Graph(e).reset_forwarded().forward();
  Graph(f).reset_forwarded().forward();
  REQUIRE(e->value().shape() == f->value().shape());
  CHECK(e->value() == Close(f->value()).epsilon(eps));
}

#endif // GINN_CHECK_NODE_H

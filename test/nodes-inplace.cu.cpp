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

#define CATCH_CONFIG_MAIN // so that Catch is responsible for main()
#ifndef GINN_ENABLE_GPU
#define GINN_DOUBLE_PRECISION // grad checks require double precision
#endif

#include <catch2/catch.hpp>

#include <iostream>

#include <ginn/node/inplace.h>
#include <ginn/node/nlnode.h>

#include "check_node.h"
#include "testutil.h"

using namespace ginn;

#ifdef GINN_ENABLE_GPU
constexpr bool gpu_enabled = true;
#else
constexpr bool gpu_enabled = false;
#endif

// TODO: Add checks to ensure InPlace nodes do not spend extra mem

// clang-format off

TEMPLATE_TEST_CASE("InPlaceAdd", "[inplace][arithmetic]", Real, Half) {
  using Scalar = TestType;
  auto W = Random({2, 3})->cast<Scalar>();
  auto V = Random({2, 3})->cast<Scalar>();
  auto U = Random({2, 3})->cast<Scalar>();

  auto a1 = Add(W, V, U);
  auto a2 = Add(W, V, V);
  Graph(a1).forward();
  Graph(a2).forward();

  // Need one level of indirection because of how gradcheck perturbs values and
  //   how in-place nodes reuse value tensors. Hence the multiply by 1. This
  //   only applies to testing.
  check(InPlaceAdd(W * 1, V, U), a1);
  check(InPlaceAdd(W * 1, V, V), a2);
  if constexpr (not gpu_enabled and std::is_same_v<Scalar, Real>) {
    check_grad(InPlaceAdd(W * 1, V, U), {W, V, U});
    check_grad(InPlaceAdd(W * 1, V, V), {W, V}   );
  }
  if constexpr (gpu_enabled and ginn::is_floating_point_v<Scalar>) {
    auto [W_, V_, U_] = to_gpu(W, V, U);
    compare_devices(InPlaceAdd(W * 1 , V , U ), {W , V , U },
                    InPlaceAdd(W_ * 1, V_, U_), {W_, V_, U_});
    compare_devices(InPlaceAdd(W * 1 , V , V ), {W , V },
                    InPlaceAdd(W_ * 1, V_, V_), {W_, V_});
  }
}

TEMPLATE_TEST_CASE("InPlaceAddScalar", "[inplace][arithmetic]", Real, Half) {
  using Scalar = TestType;
  auto W = Random({2, 3})->cast<Scalar>();

  auto a1 = W + 3.14;
  auto a2 = W - 5;
  Graph(a1).forward();
  Graph(a2).forward();

  check(InPlaceAddScalar(1 * W, 3.14), a1);
  check(InPlaceAddScalar(1 * W, -5), a2);
  if constexpr (not gpu_enabled and std::is_same_v<Scalar, Real>) {
    check_grad(InPlaceAddScalar(W * 1, 3.14), {W});
    check_grad(InPlaceAddScalar(W * 1, -5),   {W});
  }
  if constexpr (gpu_enabled and ginn::is_floating_point_v<Scalar>) {
    auto [W_] = to_gpu(W);
    compare_devices(InPlaceAddScalar(W  * 1, 3.14), {W },
                    InPlaceAddScalar(W_ * 1, 3.14), {W_});
    compare_devices(InPlaceAddScalar(W  * 1, -5), {W },
                    InPlaceAddScalar(W_ * 1, -5), {W_});
  }
}

TEMPLATE_TEST_CASE("InPlaceCwiseProd", "[inplace][arithmetic]", Real, Half) {
  using Scalar = TestType;
  auto W = Random({2, 3, 2})->cast<Scalar>();
  auto V = Random({2, 3, 2})->cast<Scalar>();

  auto p = CwiseProd(W, V);
  Graph(p).forward();

  check(InPlaceCwiseProd(1 * W, V), p);
  if constexpr (not gpu_enabled and std::is_same_v<Scalar, Real>) {
    check_grad(InPlaceCwiseProd(1 * W, V), {W, V});
  }
  if constexpr (gpu_enabled and ginn::is_floating_point_v<Scalar>) {
    auto [W_, V_] = to_gpu(W, V);
    compare_devices(InPlaceCwiseProd(1 * W , V ), {W , V },
                    InPlaceCwiseProd(1 * W_, V_), {W_, V_});
  }
}

TEMPLATE_TEST_CASE("InPlaceProdScalar", "[inplace][arithmetic]", Real, Half) {
  using Scalar = TestType;
  auto W = Random({2, 3})->cast<Scalar>();

  auto p1 = W * 3.14;
  auto p2 = W * -5;
  Graph(p1).forward();
  Graph(p2).forward();

  check(InPlaceProdScalar(1 * W, 3.14), p1);
  check(InPlaceProdScalar(1 * W, -5), p2);

  if constexpr (not gpu_enabled and std::is_same_v<Scalar, Real>) {
    check_grad(InPlaceProdScalar(W * 1, 3.14), {W});
    check_grad(InPlaceProdScalar(W * 1, -5),   {W});
  }
  if constexpr (gpu_enabled and ginn::is_floating_point_v<Scalar>) {
    auto [W_] = to_gpu(W);
    compare_devices(InPlaceProdScalar(W  * 1, 3.14), {W },
                    InPlaceProdScalar(W_ * 1, 3.14), {W_});
    compare_devices(InPlaceProdScalar(W  * 1, -5), {W },
                    InPlaceProdScalar(W_ * 1, -5), {W_});
  }
}

TEMPLATE_TEST_CASE("InPlaceMask", "[inplace]", Real, Half) {
  using Scalar = TestType;
  auto W  = Random({2, 3, 2})->cast<Scalar>();
  auto m1 = Random({2, 3, 2})->cast<Scalar>();
  auto m2 = Random({2, 3, 1})->cast<Scalar>();
  auto m3 = Random({2, 1, 1})->cast<Scalar>();

  auto set_mask = [](auto& m) {
    m->value() = (m->value().t() > Raw<Scalar>(0)).template cast<Raw<Scalar>>();
  };

  set_mask(m1);
  set_mask(m2);
  set_mask(m3);

  if constexpr (not gpu_enabled and std::is_same_v<Scalar, Real>) {
    check_grad(InPlaceMask(W * 1, m1, 3. ), {W});
    check_grad(InPlaceMask(W * 1, m2, -3.), {W});
    check_grad(InPlaceMask(W * 1, m3, 0. ), {W});
  }
  if constexpr (gpu_enabled and ginn::is_floating_point_v<Scalar>) {
    auto [W_, m1_, m2_, m3_] = to_gpu(W, m1, m2, m3);
    compare_devices(InPlaceMask(W, m1,  3.), {W}, InPlaceMask(W_, m1_,  3.), {W_});
    compare_devices(InPlaceMask(W, m2, -3.), {W}, InPlaceMask(W_, m2_, -3.), {W_});
    compare_devices(InPlaceMask(W, m3,  0.), {W}, InPlaceMask(W_, m3_,  0.), {W_});
  }
}

TEMPLATE_TEST_CASE("InPlaceSigmoid", "[inplace][nlnode]", Real, Half) {
  using Scalar = TestType;
  auto W = Random({2, 3})->cast<Scalar>();

  auto s = Sigmoid(W);
  Graph(s).forward();

  check(InPlaceSigmoid(1 * W), s);
  if constexpr (not gpu_enabled and std::is_same_v<Scalar, Real>) {
    check_grad(InPlaceSigmoid(1 * W), {W});
  }
  if constexpr (gpu_enabled and ginn::is_floating_point_v<Scalar>) {
    auto [W_] = to_gpu(W);
    compare_devices(InPlaceSigmoid(1 * W ), {W },
                    InPlaceSigmoid(1 * W_), {W_});
  }
}

TEMPLATE_TEST_CASE("LayerNorm", "[layernorm][inplace]", Real, Half) {
  using Scalar = TestType;
  auto x = Random({3, 2, 4})->cast<Scalar>();
  using s = Raw<Scalar>;
  x->value() = x->value().t() * s(2.5) - s(2);

  auto y = LayerNorm(x);
  Graph(y).forward();

  check(InPlaceLayerNorm(x * 1.), y);

  if constexpr (not gpu_enabled and std::is_same_v<Scalar, Real>) {
    check_grad(InPlaceLayerNorm(1 * x), {x}, false);
  }
  if constexpr (gpu_enabled and ginn::is_floating_point_v<Scalar>) {
    auto [x_] = to_gpu(x);
    compare_devices(x  + InPlaceLayerNorm(1 * x ), {x },
                    x_ + InPlaceLayerNorm(1 * x_), {x_},
                    std::is_same_v<Scalar, Real> ? 1e-4 : 2e-3);
  }
}
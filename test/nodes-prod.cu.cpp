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

#include <ginn/node/affine.h>
#include <ginn/node/layout.h>
#include <ginn/node/prod.h>

#include "check_node.h"
#include "testutil.h"

using namespace ginn;

#ifdef GINN_ENABLE_GPU
constexpr bool gpu_enabled = true;
#else
constexpr bool gpu_enabled = false;
#endif

// clang-format off

TEMPLATE_TEST_CASE("Prod", "[prod]", Real, Half) {
  using Scalar = TestType;
  auto W = Values<2>({{1, 2, 3},
                      {4, 5, 6}})->cast<Scalar>();
  auto V = Values<2>({{ 0.6,  0.5},
                      { 0.4, -0.1},
                      {-0.2, -0.3}})->cast<Scalar>();

  auto WV = Values<2>({{0.8, -0.6},
                       {3.2, -0.3}})->cast<Scalar>();

  Real eps = std::is_same_v<Scalar, Half> ? 1e-2 : 1e-6; // TODO: 😢
  Real eps2 = std::is_same_v<Scalar, Half> ? 1e-2 : 1e-4;

  check(Prod(W, V), WV, eps);
  check(W * V,      WV, eps);
  if constexpr (not gpu_enabled and std::is_same_v<Scalar, Real>) {
    check_grad(Prod(W, V), {W, V}, true, eps2);
    check_grad(W * V,      {W, V}, true, eps2);
  }
  if constexpr (gpu_enabled and ginn::is_floating_point_v<Scalar>) {
    auto [W_, V_] = to_gpu(W, V);
    compare_devices(Prod(W, V), {W, V}, Prod(W_, V_), {W_, V_}, eps2);
    compare_devices(W * V,      {W, V}, W_ * V_,      {W_, V_}, eps2);
  }
}

TEMPLATE_TEST_CASE("BatchedProd", "[prod]", Real, Half) {
  using Scalar = TestType;

  DataPtr<Scalar> a, b;
  Real eps = std::is_same_v<Scalar, Half> ? 1e-2 : 1e-6; // TODO: 😢
  Real eps2 = std::is_same_v<Scalar, Half> ? 4e-2 : 1e-4;

  SECTION("Basic") {
    a = Random({2, 3, 4})->cast<Scalar>();
    b = Random({3, 5, 4})->cast<Scalar>();
    a->value() = a->value().t() + Raw<Scalar>(1.);
    b->value() = b->value().t() - Raw<Scalar>(1.);
    auto c = BatchedProd(a, b);

    auto c0 = Chip(c, 0, 2);
    auto c1 = Chip(c, 1, 2);
    auto c2 = Chip(c, 2, 2);
    auto c3 = Chip(c, 3, 2);

    auto a0 = Chip(a, 0, 2), b0 = Chip(b, 0, 2);
    auto a1 = Chip(a, 1, 2), b1 = Chip(b, 1, 2);
    auto a2 = Chip(a, 2, 2), b2 = Chip(b, 2, 2);
    auto a3 = Chip(a, 3, 2), b3 = Chip(b, 3, 2);

    auto c0_ = a0 * b0;
    auto c1_ = a1 * b1;
    auto c2_ = a2 * b2;
    auto c3_ = a3 * b3;

    check(c0, c0_, eps);
    check(c1, c1_, eps);
    check(c2, c2_, eps);
    check(c3, c3_, eps);
  }

  SECTION("High rank") {
    a = Random({2, 3, 2, 2})->cast<Scalar>();
    b = Random({3, 5, 2, 2})->cast<Scalar>();
    a->value() = a->value().t() + Raw<Scalar>(1.);
    b->value() = b->value().t() - Raw<Scalar>(1.);
    auto c = BatchedProd(a, b);

    auto ChipTwice = [](auto x, Size i, Size j) {
      return Chip(Chip(x, j, 3), i, 2);
    };

    auto c00 = ChipTwice(c, 0, 0);
    auto c01 = ChipTwice(c, 0, 1);
    auto c10 = ChipTwice(c, 1, 0);
    auto c11 = ChipTwice(c, 1, 1);

    auto a00 = ChipTwice(a, 0, 0), b00 = ChipTwice(b, 0, 0);
    auto a01 = ChipTwice(a, 0, 1), b01 = ChipTwice(b, 0, 1);
    auto a10 = ChipTwice(a, 1, 0), b10 = ChipTwice(b, 1, 0);
    auto a11 = ChipTwice(a, 1, 1), b11 = ChipTwice(b, 1, 1);

    auto c00_ = a00 * b00;
    auto c01_ = a01 * b01;
    auto c10_ = a10 * b10;
    auto c11_ = a11 * b11;

    check(c00, c00_, eps);
    check(c01, c01_, eps);
    check(c10, c10_, eps);
    check(c11, c11_, eps);
  }

  if constexpr (not gpu_enabled and std::is_same_v<Scalar, Real>) {
    check_grad(BatchedProd(a, b), {a, b}, false, eps2);
  }
  if constexpr (gpu_enabled and ginn::is_floating_point_v<Scalar>) {
    auto [a_, b_] = to_gpu(a, b);
    compare_devices(BatchedProd(a , b) , {a , b },
                    BatchedProd(a_, b_), {a_, b_}, eps2);
  }
}

TEMPLATE_TEST_CASE("Affine", "[affine]", Real, Half) {
  using Scalar = TestType;
  Real eps = std::is_same_v<Scalar, Half> ? 2e-3 : 1e-6; // TODO: 😢
  Real eps2 = std::is_same_v<Scalar, Half> ? 4e-2 : 1e-4;

  auto W = Values<2>({{1, 2, 3},
                      {4, 5, 6}})->cast<Scalar>();
  auto V = Values<2>({{ 0.6},
                      { 0.4},
                      {-0.2}})->cast<Scalar>();
  auto b = Values<2>({{0.01},
                      {0.02}})->cast<Scalar>();

  SECTION("Affine") {
    auto WVb = Values<2>({{0.81},
                          {3.22}})->cast<Scalar>();

    check(Affine(W, V, b), WVb, eps);
    check(W * V + b,       WVb, eps);

    if constexpr (not gpu_enabled and std::is_same_v<Scalar, Real>) {
      check_grad(Affine(W, V, b),  {W, V, b}, true);
      check_grad(W * V + b,        {W, V, b}, true);
    }
    if constexpr (gpu_enabled and ginn::is_floating_point_v<Scalar>) {
      auto [W_, V_, b_] = to_gpu(W, V, b);
      compare_devices(Affine(W,  V,  b),  {W,  V,  b },
                      Affine(W_, V_, b_), {W_, V_, b_}, eps2);
      compare_devices(W  * V  + b,  {W,  V,  b },
                      W_ * V_ + b_, {W_, V_, b_}, eps2);
    }
  }

  SECTION("AffineSigmoid") {
    auto sigmWVb = Values<2>({{0.692109},
                              {0.96158 }})->cast<Scalar>();

    check(Affine(SigmoidOp<Scalar>(), W, V, b), sigmWVb, eps);
    check(Affine<SigmoidOp>(W, V, b),           sigmWVb, eps);
    
    if constexpr (not gpu_enabled and std::is_same_v<Scalar, Real>) {
      check_grad(Affine(SigmoidOp<Scalar>(), W, V, b), {W, V, b}, true, eps2);
      check_grad(Affine<SigmoidOp>(W, V, b),           {W, V, b}, true, eps2);
    }
    if constexpr (gpu_enabled and ginn::is_floating_point_v<Scalar>) {
      auto [W_, V_, b_] = to_gpu(W, V, b);
      compare_devices(Affine(SigmoidOp<Scalar, CPU>(), W , V , b ), {W , V , b },
                      Affine(SigmoidOp<Scalar, GPU>(), W_, V_, b_), {W_, V_, b_}, eps2);
      compare_devices(Affine<SigmoidOp>(W , V , b ), {W , V , b },
                      Affine<SigmoidOp>(W_, V_, b_), {W_, V_, b_}, eps2);
    }
  }

  SECTION("AffineSoftmax") {
    auto smaxWVb = Values<2>({{0.0824133},
                              {0.917587 }})->cast<Scalar>();
    check(Affine<SoftmaxOp>(W, V, b), smaxWVb, eps);
    if constexpr (not gpu_enabled and std::is_same_v<Scalar, Real>) {
      check_grad(Affine<SoftmaxOp>(W, V, b), {W, V, b}, true, eps2);
    }
    if constexpr (gpu_enabled and ginn::is_floating_point_v<Scalar>) {
      auto [W_, V_, b_] = to_gpu(W, V, b);
      compare_devices(Affine<SoftmaxOp>(W , V , b ), {W , V , b },
                      Affine<SoftmaxOp>(W_, V_, b_), {W_, V_, b_}, eps2);
    }
  }

  SECTION("Other nonlins") {
    if constexpr (not gpu_enabled and std::is_same_v<Scalar, Real>) {
      check_grad(Affine<TanhOp>(W, V, b),      {W, V, b}, true, eps2);
      check_grad(Affine<ReluOp>(W * 10, V, b), {W, V, b}, true, eps2);
      check_grad(Affine<Gelu2Op>(W, V, b),     {W, V, b}, true, eps2);
      check_grad(Affine<GeluOp>(W, V, b),      {W, V, b}, true, eps2);
    }
    if constexpr (gpu_enabled and ginn::is_floating_point_v<Scalar>) {
      auto [W_, V_, b_] = to_gpu(W, V, b);
      compare_devices(Affine<TanhOp>(W , V , b ), {W , V , b },
                      Affine<TanhOp>(W_, V_, b_), {W_, V_, b_}, eps2);
      compare_devices(Affine<ReluOp>(W  * 10, V , b ), {W , V , b },
                      Affine<ReluOp>(W_ * 10, V_, b_), {W_, V_, b_}, eps2);
      compare_devices(Affine<Gelu2Op>(W , V , b ), {W , V , b },
                      Affine<Gelu2Op>(W_, V_, b_), {W_, V_, b_}, eps2);
      compare_devices(Affine<GeluOp>(W , V , b ), {W , V , b },
                      Affine<GeluOp>(W_, V_, b_), {W_, V_, b_}, eps2);
    }
  }
}

TEMPLATE_TEST_CASE("Affine w/ broadcast", "[affine]", Real, Half) {
  using Scalar = TestType;
  Real eps = std::is_same_v<Scalar, Half> ? 2e-3 : 1e-6; // TODO: 😢
  Real eps2 = std::is_same_v<Scalar, Half> ? 2e-2 : 1e-4;
  auto W = Values<2>({{1, 2, 3},
                      {4, 5, 6}})->cast<Scalar>();
  auto V = Values<2>({{ 6,  5},
                      { 4, -1},
                      {-2, -3}})->cast<Scalar>();
  auto b = Values<2>({{0.1},
                      {0.2}})->cast<Scalar>();

  auto WVb = Values<2>({{ 8.1, -5.9},
                        {32.2, -2.8}})->cast<Scalar>();

  check(Affine(W, V, b), WVb, eps);

  if constexpr (not gpu_enabled and std::is_same_v<Scalar, Real>) {
    check_grad(Affine(W, V, b), {W, V, b}, true);
  }
  if constexpr (gpu_enabled and ginn::is_floating_point_v<Scalar>) {
    auto [W_, V_, b_] = to_gpu(W, V, b);
    compare_devices(Affine(W,  V,  b),  {W,  V,  b },
                    Affine(W_, V_, b_), {W_, V_, b_}, eps2);
  }
}

TEMPLATE_TEST_CASE("Affine w/ high rank", "[affine]", Real, Half) {
  using Scalar = TestType;
  Real eps = std::is_same_v<Scalar, Half> ? 2e-3 : 1e-6; // TODO: 😢
  Real eps2 = std::is_same_v<Scalar, Half> ? 2e-3 : 1e-4;
  auto W = Values<2>({{1, 2, 3}, // 2 x 3
                      {4, 5, 6}})->cast<Scalar>();
  auto V = Values<3>({{{ 6,  5},{ 6,  5}}, // 3 x 2 x 2
                      {{ 4, -1},{ 4, -1}},
                      {{-2, -3},{-2, -3}}})->cast<Scalar>();
  auto b = Values<1>({0.1, // 2
                      0.2})->cast<Scalar>();

  auto WVb = Values<3>({{{ 8.1, -5.9},{ 8.1, -5.9}}, // 2 x 2 x 2
                        {{32.2, -2.8},{32.2, -2.8}}})->cast<Scalar>();

  check(Affine(W, V, b), WVb, eps);

  if constexpr (not gpu_enabled and std::is_same_v<Scalar, Real>) {
    check_grad(Affine(W, V, b), {W, V, b}, true);
  }
  if constexpr (gpu_enabled and ginn::is_floating_point_v<Scalar>) {
    auto [W_, V_, b_] = to_gpu(W, V, b);
    compare_devices(Affine(W,  V,  b),  {W,  V,  b },
                    Affine(W_, V_, b_), {W_, V_, b_}, eps2);
  }
}
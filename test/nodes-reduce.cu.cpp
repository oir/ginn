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
#include <cppitertools/zip.hpp>

#include <iostream>

#include <ginn/node/common.h>

#include "check_node.h"
#include "testutil.h"

using namespace ginn;

#ifdef GINN_ENABLE_GPU
constexpr bool gpu_enabled = true;
#else
constexpr bool gpu_enabled = false;
#endif

// clang-format off

TEMPLATE_TEST_CASE("Reduce", "[reduce]", Real, Half) {
  using Scalar = TestType;
  auto W = Values<2>({{1, 2, 3},
                      {4, 5, 6}})->cast<Scalar>();

#define BASIC_REDUCE_SECTION(F, expected)                                      \
  SECTION(#F) {                                                                \
    auto y = Values<0>(expected)->cast<Scalar>();                              \
    check(F(W), y);                                                            \
                                                                               \
    if constexpr (not gpu_enabled and std::is_same_v<Scalar, Real>) {          \
      check_grad(F(W), {W}, true);                                             \
    }                                                                          \
    if constexpr (gpu_enabled and ginn::is_floating_point_v<Scalar>) {         \
      auto [W_] = to_gpu(W);                                                   \
      compare_devices(F(W), {W}, F(W_), {W_});                                 \
    }                                                                          \
  }

  BASIC_REDUCE_SECTION(Sum, 21.)
  BASIC_REDUCE_SECTION(Mean, 3.5)
  BASIC_REDUCE_SECTION(Variance, 35./12.)
}

TEMPLATE_TEST_CASE("AxisSum", "[reduce]", Real, Half) {
  using Scalar = TestType;
  auto V    = Values<3>({{{1, 2, 3},
                          {4, 5, 6}},
                         {{.1, .2, .3},
                          {.4, .5, .6}}})->cast<Scalar>();
  auto V0   = Values<2>({{1.1, 2.2, 3.3},
                         {4.4, 5.5, 6.6}})->cast<Scalar>();
  auto V01  = Values<1>({5.5, 7.7, 9.9})->cast<Scalar>();
  auto V012 = Values<0>(23.1)->cast<Scalar>();
  auto V1   = Values<2>({{5 , 7 , 9 },
                         {.5, .7, .9}})->cast<Scalar>();
  auto V12  = Values<1>({21,
                         2.1})->cast<Scalar>();
  auto V2   = Values<2>({{ 6,
                          15},
                         {.6,
                          1.5}})->cast<Scalar>();
  auto V02  = Values<1>({ 6.6,
                         16.5})->cast<Scalar>();
  Real eps = std::is_same_v<Scalar, Half> ? 1e-3 : 1e-6;

  std::vector<std::vector<Size>> indices{
      {0}, {0, 1}, {0, 1, 2}, {1}, {1, 2}, {2}, {0, 2}};
  std::vector<DataPtr<Scalar>> expected{V0, V01, V012, V1, V12, V2, V02};

  for (auto&& [index, y] : iter::zip(indices, expected)) {
    check(AxisSum(V, index), y, eps);
  }
  CHECK_THROWS(AxisSum(V, {0, 0}));
  CHECK_THROWS(AxisSum(V, {2, 0}));

  if constexpr (not gpu_enabled and std::is_same_v<Scalar, Real>) {
    for (auto&& index : indices) { check_grad(AxisSum(V, index), {V}, true); }
  }
  if constexpr (gpu_enabled and ginn::is_floating_point_v<Scalar>) {
    auto [V_] = to_gpu(V);
    for (auto&& index : indices) {
      compare_devices(AxisSum(V, index), {V}, AxisSum(V_, index), {V_});
    }
  }
}

// clang-format on
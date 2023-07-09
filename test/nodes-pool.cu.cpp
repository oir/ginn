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

#include <algorithm>
#include <iostream>

#include <ginn/node/pool.h>

#include "check_node.h"

using namespace ginn;

#ifdef GINN_ENABLE_GPU
constexpr bool gpu_enabled = true;
#else
constexpr bool gpu_enabled = false;
#endif

// clang-format off

TEMPLATE_TEST_CASE("MaxPool2d", "[pool]", Real, Half) {
  using Scalar = TestType;
  auto x = Values<4>({{{{1}, {4}, {7}},
                       {{2}, {5}, {8}},
                       {{3}, {6}, {9}}}})->cast<Scalar>();
  REQUIRE(x->shape() == Shape{1, 3, 3, 1});

  auto y = Values<4>({{{{5}, {8}, {8}},
                       {{6}, {9}, {9}},
                       {{6}, {9}, {9}}}})->cast<Scalar>();
  REQUIRE(y->shape() == Shape{1, 3, 3, 1});

  auto y2 = Values<4>({{{{5}, {8}, {8}},
                        {{6}, {9}, {9}}}})->cast<Scalar>();
  REQUIRE(y2->shape() == Shape{1, 2, 3, 1});

  auto y3 = Values<4>({{{{5}},
                        {{6}}}})->cast<Scalar>();
  REQUIRE(y3->shape() == Shape{1, 2, 1, 1});

  SECTION("Basic")            { check(MaxPool2d(x, 2, 2),       y ); }
  SECTION("Row stride")       { check(MaxPool2d(x, 2, 2, 2),    y2); }
  SECTION("Row & col stride") { check(MaxPool2d(x, 2, 2, 2, 3), y3); }
  SECTION("Grad or cuda") {
    if constexpr (not gpu_enabled and std::is_same_v<Scalar, Real>) {
      check_grad(MaxPool2d(x, 2, 2),       {x}, true); 
      check_grad(MaxPool2d(x, 2, 2, 2),    {x}, true); 
      check_grad(MaxPool2d(x, 2, 2, 2, 3), {x}, true); 
    }
    if constexpr (gpu_enabled and ginn::is_floating_point_v<Scalar>) {
      auto [x_] = to_gpu(x);
      compare_devices(MaxPool2d(x, 2, 2),       {x}, MaxPool2d(x_, 2, 2),       {x_}); 
      compare_devices(MaxPool2d(x, 2, 2, 2),    {x}, MaxPool2d(x_, 2, 2, 2),    {x_}); 
      compare_devices(MaxPool2d(x, 2, 2, 2, 3), {x}, MaxPool2d(x_, 2, 2, 2, 3), {x_}); 
    }
  }
}

TEMPLATE_TEST_CASE("MaxPool1d", "[pool]", Real, Half) {
  using Scalar = TestType;
  auto x = Values<3>({{{9}, {6}, {3}},
                      {{2}, {5}, {8}},
                      {{4}, {1}, {7}}})->cast<Scalar>();
  REQUIRE(x->shape() == Shape{3, 3, 1});

  SECTION("Basic") {
    auto y = Values<3>({{{9}, {6}, {3}},
                        {{5}, {8}, {8}},
                        {{4}, {7}, {7}}})->cast<Scalar>();
    REQUIRE(y->shape() == Shape{3, 3, 1});
    check(MaxPool1d(x, 2), y);
  }

  SECTION("Stride") {
    auto y = Values<3>({{{9}, {3}},
                        {{5}, {8}},
                        {{4}, {7}}})->cast<Scalar>();
    REQUIRE(y->shape() == Shape{3, 2, 1});
    check(MaxPool1d(x, 2, 2), y);
  }

  SECTION("Grad or cuda") {
    if constexpr (not gpu_enabled and std::is_same_v<Scalar, Real>) {
      check_grad(MaxPool1d(x, 2),    {x}, true);
      check_grad(MaxPool1d(x, 2, 2), {x}, true);
    }
    if constexpr (gpu_enabled and ginn::is_floating_point_v<Scalar>) {
      auto [x_] = to_gpu(x);
      compare_devices(MaxPool1d(x, 2),    {x}, MaxPool1d(x_, 2),    {x_});
      compare_devices(MaxPool1d(x, 2, 2), {x}, MaxPool1d(x_, 2, 2), {x_});
    }
  }
}

// clang-format on
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

#include <ginn/node/conv.h>

#include "check_node.h"

using namespace ginn;

#ifdef GINN_ENABLE_GPU
constexpr bool gpu_enabled = true;
#else
constexpr bool gpu_enabled = false;
#endif

// clang-format off

// With Eigen::half, this does not build (with cuda)
// With __half, it builds but crashes at runtime
TEMPLATE_TEST_CASE("Conv2d", "[conv]", Real) {
  using Scalar = TestType;
  auto x = Values<4>({{{{1}, {4}, {7}},
                       {{2}, {5}, {8}},
                       {{3}, {6}, {9}}}})->cast<Scalar>();
  REQUIRE(x->shape() == Shape{1, 3, 3, 1});

  auto f = Values<4>({{{{1, 3},
                        {2, 4}}}})->cast<Scalar>();
  REQUIRE(f->shape() == Shape{1, 1, 2, 2});

  auto y = Values<4>({{{{37}, {67}, {23}},
                       {{47}, {77}, {26}},
                       {{21}, {33}, { 9}}}})->cast<Scalar>();
  REQUIRE(y->shape() == Shape{1, 3, 3, 1});

  auto y2 = Values<4>({{{{37}, {67}, {23}},
                        {{21}, {33}, { 9}}}})->cast<Scalar>();
  REQUIRE(y2->shape() == Shape{1, 2, 3, 1});

  auto y3 = Values<4>({{{{37}},
                        {{21}}}})->cast<Scalar>();
  REQUIRE(y3->shape() == Shape{1, 2, 1, 1});

  SECTION("Basic")            { check(Conv2d(x, f),       y ); }
  SECTION("Row stride")       { check(Conv2d(x, f, 2, 1), y2); }
  SECTION("Row & col stride") { check(Conv2d(x, f, 2, 3), y3); }

  SECTION("Grad or cuda") {
    if constexpr (not gpu_enabled and std::is_same_v<Scalar, Real>) {
      check_grad(Conv2d(x, f),       {x, f}, true);
      check_grad(Conv2d(x, f, 2, 1), {x, f}, true);
      check_grad(Conv2d(x, f, 2, 3), {x, f}, true);
    }
    if constexpr (gpu_enabled and ginn::is_floating_point_v<Scalar>) {
      auto [x_, f_] = to_gpu(x, f);
      compare_devices(Conv2d(x, f),       {x, f}, Conv2d(x_, f_),       {x_, f_});
      compare_devices(Conv2d(x, f, 2, 1), {x, f}, Conv2d(x_, f_, 2, 1), {x_, f_});
      compare_devices(Conv2d(x, f, 2, 3), {x, f}, Conv2d(x_, f_, 2, 3), {x_, f_});
    }
  }
}

TEMPLATE_TEST_CASE("Conv2d 2", "[conv]", Real) {
  using Scalar = TestType;

  auto x = Values<4>({{{{1}, {5}, {9}, {3}},
                       {{2}, {6}, {0}, {4}},
                       {{3}, {7}, {1}, {5}},
                       {{4}, {8}, {2}, {6}}}})->cast<Scalar>();
  REQUIRE(x->shape() == Shape{1, 4, 4, 1});

  auto f = Values<4>({{{{1, 4, 7},
                        {2, 5, 8},
                        {3, 6, 9}}}})->cast<Scalar>();
  REQUIRE(f->shape() == Shape{1, 1, 3, 3});

  auto y = Values<4>({{{{111}, {141}, {133}, {57}},
                       {{178}, {178}, {178}, {74}},
                       {{217}, {153}, {183}, {85}},
                       {{145}, {102}, {120}, {55}}}})->cast<Scalar>();
  REQUIRE(y->shape() == Shape{1, 4, 4, 1});

  SECTION("Basic") {
    check(Conv2d(x, f), y);
  }
  SECTION("Grad or cuda") {
    if constexpr (not gpu_enabled and std::is_same_v<Scalar, Real>) {
      check_grad(Conv2d(x, f), {x, f}, true);
    }
    if constexpr (gpu_enabled and ginn::is_floating_point_v<Scalar>) {
      auto [x_, f_] = to_gpu(x, f);
      compare_devices(Conv2d(x, f), {x, f}, Conv2d(x_, f_), {x_, f_});
    }
  }
}

TEMPLATE_TEST_CASE("Conv2d 3", "[conv]", Real) {
  using Scalar = TestType;

  auto x = Values<4>({{{ {2}, {3} }}})->cast<Scalar>();
  auto f = Values<4>({{{{4, 5, 6}}}})->cast<Scalar>();
  auto y = Values<4>({{{{23}}}})->cast<Scalar>();

  REQUIRE(x->shape() == Shape{1, 1, 2, 1});
  REQUIRE(f->shape() == Shape{1, 1, 1, 3});
  REQUIRE(y->shape() == Shape{1, 1, 1, 1});

  SECTION("Strided") {
    check(Conv2d(x, f, 1, 2), y);

    if constexpr (not gpu_enabled and std::is_same_v<Scalar, Real>) {
      check_grad(Conv2d(x, f, 1, 2), {x, f}, true);
    }
    if constexpr (gpu_enabled and ginn::is_floating_point_v<Scalar>) {
      auto [x_, f_] = to_gpu(x, f);
      compare_devices(Conv2d(x , f , 1, 2), {x , f},
                      Conv2d(x_, f_, 1, 2), {x_, f_});
    }
  }
}

TEMPLATE_TEST_CASE("Conv1d", "[forward]", Real) {
  using Scalar = TestType;

  auto x = Values<3>({{{1}, {4}, {7}},
                      {{2}, {5}, {8}},
                      {{3}, {6}, {9}}})->cast<Scalar>();
  REQUIRE(x->shape() == Shape{3, 3, 1});

  auto f = Values<3>({{{1, 4},
                       {2, 5},
                       {3, 6}}})->cast<Scalar>();
  REQUIRE(f->shape() == Shape{1, 3, 2});

  auto y = Values<3>({{{91}, {154}, {50}}})->cast<Scalar>();
  REQUIRE(y->shape() == Shape{1, 3, 1});

  auto y2 = Values<3>({{{91}, {50}}})->cast<Scalar>();
  REQUIRE(y2->shape() == Shape{1, 2, 1});

  SECTION("Basic")  { check(Conv1d(x, f),    y ); }
  SECTION("Stride") { check(Conv1d(x, f, 2), y2); }
  SECTION("Grad or cuda") {
    if constexpr (not gpu_enabled and std::is_same_v<Scalar, Real>) {
      check_grad(Conv1d(x, f),    {x, f}, true);
      check_grad(Conv1d(x, f, 2), {x, f}, true);
    }
    if constexpr (gpu_enabled and ginn::is_floating_point_v<Scalar>) {
      auto [x_, f_] = to_gpu(x, f);
      compare_devices(Conv1d(x, f),    {x, f}, Conv1d(x_, f_),    {x_, f_});
      compare_devices(Conv1d(x, f, 2), {x, f}, Conv1d(x_, f_, 2), {x_, f_});
    }
  }
}

TEMPLATE_TEST_CASE("Conv1d more filters", "[forward]", Real) {
  using Scalar = TestType;

  auto x = Values<3>({{{1}, {4}, {7}},
                      {{2}, {5}, {8}},
                      {{3}, {6}, {9}}})->cast<Scalar>();
  REQUIRE(x->shape() == Shape{3, 3, 1});

  auto f = Values<3>({{{1, 4},
                       {2, 5},
                       {3, 6}},
                      {{1.5, 4.5},
                       {2.5, 5.5},
                       {3.5, 6.5}}})->cast<Scalar>();
  REQUIRE(f->shape() == Shape{2, 3, 2});

  auto y = Values<3>({{{ 91  }, {154  }, {50}},
                      {{101.5}, {173.5}, {62}}})->cast<Scalar>();
  REQUIRE(y->shape() == Shape{2, 3, 1});

  auto y2 = Values<3>({{{ 91  }, {50}},
                       {{101.5}, {62}}})->cast<Scalar>();
  REQUIRE(y2->shape() == Shape{2, 2, 1});

  SECTION("Basic")  { check(Conv1d(x, f),    y ); }
  SECTION("Stride") { check(Conv1d(x, f, 2), y2); }
  SECTION("Grad or cuda") {
    if constexpr (not gpu_enabled and std::is_same_v<Scalar, Real>) {
      check_grad(Conv1d(x, f),    {x, f});
      check_grad(Conv1d(x, f, 2), {x, f});
    }
    if constexpr (gpu_enabled and ginn::is_floating_point_v<Scalar>) {
      auto [x_, f_] = to_gpu(x, f);
      compare_devices(Conv1d(x, f),    {x, f}, Conv1d(x_, f_),    {x_, f_});
      compare_devices(Conv1d(x, f, 2), {x, f}, Conv1d(x_, f_, 2), {x_, f_});
    }
  }
}

// clang-format on

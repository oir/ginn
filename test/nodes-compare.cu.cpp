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

#include <ginn/node/compare.h>

#include "check_node.h"
#include "testutil.h"

using namespace ginn;

#ifdef GINN_ENABLE_GPU
constexpr bool gpu_enabled = true;
#else
constexpr bool gpu_enabled = false;
#endif

TEMPLATE_TEST_CASE("Comparison", "[compare]", Real, Half, Int) {
  using Scalar = TestType;
  auto a = Values<2>({{1.}, {2.}, {3.}, {4.}, {5.}})->cast<Scalar>();
  auto b = Values<2>({{5.}, {4.}, {3.}, {2.}, {1.}})->cast<Scalar>();

  REQUIRE(a->shape() == Shape{5, 1});
  REQUIRE(b->shape() == Shape{5, 1});

  SECTION("LessThan") {
    auto y = Values<2>({{1.}, {1.}, {0.}, {0.}, {0.}})->cast<bool>();

    check(LessThan(a, b), y);
    check(a < b, y);
    if constexpr (not gpu_enabled and std::is_same_v<Scalar, Real>) {
      // TODO: Enable these after a CastNode implementation
      // check_grad(LessThan(a, b), {a, b}, true);
      // check_grad(a < b,          {a, b}, true);
    }
    if constexpr (gpu_enabled and ginn::is_floating_point_v<Scalar>) {
      compare_devices(LessThan(a, b),
                      std::initializer_list<NodePtr<Scalar, CPU>>{},
                      LessThan(a, b),
                      std::initializer_list<NodePtr<Scalar, GPU>>{});
      compare_devices(a < b,
                      std::initializer_list<NodePtr<Scalar, CPU>>{},
                      a < b,
                      std::initializer_list<NodePtr<Scalar, GPU>>{});
    }
  }
}

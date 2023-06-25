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

TEMPLATE_TEST_CASE("Add subtract", "[arithmetic]", Real, Half, Int) {
  using Scalar = TestType;

  auto a = Values<2>({{1, 4},
                      {2, 5},
                      {3, 6}})->cast<Scalar>();
  auto b = Values<2>({{-1, 4},
                      {-2, 5},
                      {-3, 6}})->cast<Scalar>();
  auto c = Values<2>({{1, -4},
                      {2, -5},
                      {3, -6}})->cast<Scalar>();

  SECTION("Add") {
    auto e = Values<2>({{0,  8},
                        {0, 10},
                        {0, 12}})->cast<Scalar>();

    check(Add(a, b), e);
    check(a + b    , e);
    if constexpr (not gpu_enabled and std::is_same_v<Scalar, Real>) {
      check_grad(Add(a, b), {a, b}, true);
      check_grad(a + b,     {a, b}, true);
    }
    if constexpr (gpu_enabled and ginn::is_floating_point_v<Scalar>) {
      auto [a_, b_] = to_gpu(a, b);
      compare_devices(Add(a,  b ), {a,  b },
                      Add(a_, b_), {a_, b_});
    }
  }

  SECTION("Add longer") {
    auto e = Values<2>({{1, 4},
                        {2, 5},
                        {3, 6}})->cast<Scalar>();

    check(Add(a, b, c), e);
    check(a + b + c   , e);
#ifndef GINN_ENABLE_GPU
    if constexpr (std::is_same_v<Scalar, Real>) {
      check_grad(Add(a, b, c),  {a, b, c}, true);
      check_grad(a + b + c,     {a, b, c}, true);
    }
#else
    if constexpr (ginn::is_floating_point_v<Scalar>) {
      auto [a_, b_, c_] = to_gpu(a, b, c);
      compare_devices(Add(a,  b,  c ), {a,  b,  c },
                      Add(a_, b_, c_), {a_, b_, c_});
      compare_devices(a  + b  + c ,    {a,  b,  c },
                      a_ + b_ + c_,    {a_, b_, c_});
    }
#endif
  }
  SECTION("Add w/ repeat") {
    auto e = Values<2>({{1, 12},
                        {2, 15},
                        {3, 18}})->cast<Scalar>();

    check(Add(a, b, a), e);
    check(a + b + a   , e);
#ifndef GINN_ENABLE_GPU
    if constexpr (std::is_same_v<Scalar, Real>) {
      check_grad(Add(a, b, a),  {a, b}, true);
      check_grad(a + b + a,     {a, b}, true);
    }
#else
    if constexpr (ginn::is_floating_point_v<Scalar>) {
      auto [a_, b_] = to_gpu(a, b);
      compare_devices(Add(a,  b,  a ), {a,  b },
                      Add(a_, b_, a_), {a_, b_});
      compare_devices(a  + b  + a ,    {a,  b },
                      a_ + b_ + a_,    {a_, b_});
    }
#endif
  }

  SECTION("Add scalar") {
    auto e = Values<2>({{2, 5},
                        {3, 6},
                        {4, 7}})->cast<Scalar>();

    Raw<Scalar> s{1};
    check(AddScalar(a, s), e);
    check(a + s          , e);
    check(s + a          , e);
#ifndef GINN_ENABLE_GPU
    if constexpr (std::is_same_v<Scalar, Real>) {
      check_grad(AddScalar(a, s), {a}, true);
      check_grad(a + s,           {a}, true);
      check_grad(s + a,           {a}, true);
    }
#else
    if constexpr (ginn::is_floating_point_v<Scalar>) {
      auto a_ = a->copy_to(gpu());
      compare_devices(AddScalar(a,  s), {a },
                      AddScalar(a_, s), {a_});
      compare_devices(a + s, {a}, a_ + s, {a_});
      compare_devices(s + a, {a}, s + a_, {a_});
    }
#endif
  }

  SECTION("Subtract") {
    auto e = Values<2>({{2, 0},
                        {4, 0},
                        {6, 0}})->cast<Scalar>();

    check(Subtract(a, b), e);
    check(a - b         , e);
#ifndef GINN_ENABLE_GPU
    if constexpr (std::is_same_v<Scalar, Real>) {
      check_grad(Subtract(a, b), {a, b}, true);
      check_grad(a - b,          {a, b}, true);
    }
#else
    if constexpr (ginn::is_floating_point_v<Scalar>) {
      auto [a_, b_] = to_gpu(a, b);
      compare_devices(Subtract(a,  b ), {a , b },
                      Subtract(a_, b_), {a_, b_});
      compare_devices(a - b, {a, b}, a_ - b_, {a_, b_});
    }
#endif
  }

  SECTION("Subtract scalar") {
    auto e = Values<2>({{ 0, -3},
                        {-1, -4},
                        {-2, -5}})->cast<Scalar>();
    check(SubtractScalar(1, a), e);
    check(1 - a,                e);
    check(1.0 - a,              e);
#ifndef GINN_ENABLE_GPU
    if constexpr (std::is_same_v<Scalar, Real>) {
      check_grad(SubtractScalar(1, a), {a}, true);
      check_grad(1 - a,                {a}, true);
      check_grad(1.0 - a,              {a}, true);
    }
#else
    if constexpr (ginn::is_floating_point_v<Scalar>) {
      auto a_ = a->copy_to(gpu());
      compare_devices(SubtractScalar(1, a ), {a },
                      SubtractScalar(1, a_), {a_});
      compare_devices(1 - a  , {a}, 1 - a_  , {a_});
      compare_devices(1.0 - a, {a}, 1.0 - a_, {a_});
    }
#endif

    auto a2 = Values<2>({{1, 4},
                         {2, 5},
                         {3, 6}})->cast<Scalar>();
    auto e2 = Values<2>({{0, 3},
                         {1, 4},
                         {2, 5}})->cast<Scalar>();
    check(AddScalar(a2, -1), e2);
    check(a2 - 1,            e2);
    check(a2 - 1.,           e2);
#ifndef GINN_ENABLE_GPU
    if constexpr (std::is_same_v<Scalar, Real>) {
      check_grad(AddScalar(a2, -1), {a}, true);
      check_grad(a2 - 1,            {a}, true);
      check_grad(a2 - 1.0,          {a}, true);
    }
#else
    if constexpr (ginn::is_floating_point_v<Scalar>) {
      auto a2_ = a2->copy_to(gpu());
      compare_devices(AddScalar(a2 , -1), {a2 },
                      AddScalar(a2_, -1), {a2_});
      compare_devices(a2 - 1  , {a2}, a2_ - 1  , {a2_});
      compare_devices(a2 - 1.0, {a2}, a2_ - 1.0, {a2_});
    }
#endif
  }

  SECTION("Negate") {
    auto e = Values<2>({{-1, -4},
                        {-2, -5},
                        {-3, -6}})->cast<Scalar>();

    check(-a, e);
#ifndef GINN_ENABLE_GPU
    if constexpr (std::is_same_v<Scalar, Real>) {
      check_grad(-a, {a}, true);
    }
#else
    if constexpr (ginn::is_floating_point_v<Scalar>) {
      auto a_ = a->copy_to(gpu());
      compare_devices(-a, {a}, -a_, {a_});
    }
#endif
  }

  SECTION("Prod scalar") {
    auto e = Values<2>({{2,  8},
                        {4, 10},
                        {6, 12}})->cast<Scalar>();

    check(ProdScalar(a, 2), e);
    check(a * 2           , e);
    check(2 * a           , e);
    check(ProdScalar(a, 2.), e);
    check(a * 2.           , e);
    check(2. * a           , e);
#ifndef GINN_ENABLE_GPU
    if constexpr (std::is_same_v<Scalar, Real>) {
      check_grad(ProdScalar(a, 2), {a}, true);
      check_grad(a * 2, {a}, true);
      check_grad(2 * a, {a}, true);
      check_grad(ProdScalar(a, 2.), {a}, true);
      check_grad(a * 2., {a}, true);
      check_grad(2. * a, {a}, true);
    }
#else
    if constexpr (ginn::is_floating_point_v<Scalar>) {
      auto a_ = a->copy_to(gpu());
      compare_devices(ProdScalar(a,  2), {a },
                      ProdScalar(a_, 2), {a_});
      compare_devices(a * 2, {a}, a_ * 2, {a_});
      compare_devices(2 * a, {a}, 2 * a_, {a_});
      compare_devices(ProdScalar(a,  2.), {a },
                      ProdScalar(a_, 2.), {a_});
      compare_devices(a * 2., {a}, a_ * 2., {a_});
      compare_devices(2. * a, {a}, 2. * a_, {a_});
    }
#endif
  }

  SECTION("CwiseProd") {
    auto e = Values<2>({{-1, 16 },
                        {-4, 25},
                        {-9, 36}})->cast<Scalar>();

    check(CwiseProd(a, b), e);
#ifndef GINN_ENABLE_GPU
    if constexpr (std::is_same_v<Scalar, Real>) {
      check_grad(CwiseProd(a, b), {a, b}, true);
    }
#else
    if constexpr (ginn::is_floating_point_v<Scalar>) {
      auto [a_, b_] = to_gpu(a, b);
      compare_devices(CwiseProd(a,  b),  {a,  b },
                      CwiseProd(a_, b_), {a_, b_});
    }
#endif
  }

  SECTION("CwiseProdAdd") {
#ifndef GINN_ENABLE_GPU
    Real eps = std::is_same_v<Scalar, Half> ? 1e-3 : 1e-6;
#endif

    SECTION("Regular") {
      auto e = Values<2>({{ 0, 12 },
                          {-2, 20},
                          {-6, 30}})->cast<Scalar>();

      check(CwiseProdAdd(a, b, c), e);
#ifndef GINN_ENABLE_GPU
      if constexpr (std::is_same_v<Scalar, Real>) {
        check_grad(CwiseProdAdd(a, b, c), {a, b, c}, true, eps);
      }
#else
      if constexpr (ginn::is_floating_point_v<Scalar>) {
        auto [a_, b_, c_] = to_gpu(a, b, c);
        compare_devices(CwiseProdAdd(a,  b,  c ), {a,  b,  c },
                        CwiseProdAdd(a_, b_, c_), {a_, b_, c_});
      }
#endif
    }

    SECTION("Regular w/ bias") {
      // a * (b+1) + c
      auto e = Values<2>({{ 1, 16 },
                          { 0, 25},
                          {-3, 36}})->cast<Scalar>();

      check(CwiseProdAdd(a, b, c, 1), e);
#ifndef GINN_ENABLE_GPU
      if constexpr (std::is_same_v<Scalar, Real>) {
        check_grad(CwiseProdAdd(a, b, c, 1), {a, b, c}, true, eps);
      }
#else
      if constexpr (ginn::is_floating_point_v<Scalar>) {
        auto [a_, b_, c_] = to_gpu(a, b, c);
        compare_devices(CwiseProdAdd(a,  b,  c,  1), {a,  b,  c },
                        CwiseProdAdd(a_, b_, c_, 1), {a_, b_, c_});
      }
#endif
    }

  //  SECTION("Broadcast") {
  //    auto b = Values<1>({-1,
  //                        -2,
  //                        -3})->cast<Scalar>();
  //    auto c = Values<1>({4,
  //                        5,
  //                        6})->cast<Scalar>();

  //    SECTION("w/o bias") {
  //      auto e = Values<2>({{ 3,   0},
  //                          { 1,  -5},
  //                          {-3, -12}})->cast<Scalar>();

  //      check(CwiseProdAdd(a, b, c), e);
  //      CHECK_(CwiseProdAdd(a, b, c), {a, b, c}, true);
  //    }

  //    SECTION("w/ bias") {
  //      auto e = Values<2>({{4,  4},
  //                          {3,  0},
  //                          {0, -6}})->cast<Scalar>();

  //      check(CwiseProdAdd(a, b, c, Scalar(1)), e);
  //      CHECK_(CwiseProdAdd(a, b, c, Scalar(1)), {a, b, c}, true);
  //    }
  //  }

  //  SECTION("Wrong shapes") {
  //    SECTION("b only column") {
  //      auto b = Values<1>({-1,
  //                          -2,
  //                          -3})->cast<Scalar>();
  //      CHECK_THROWS(Graph(CwiseProdAdd(a, b, c)).forward());
  //    }
  //    SECTION("c only column") {
  //      auto c = Values<1>({-1,
  //                          -2,
  //                          -3})->cast<Scalar>();
  //      CHECK_THROWS(Graph(CwiseProdAdd(a, b, c)).forward());
  //    }
  //    SECTION("b transposed") {
  //      auto b = Values<2>({{-1, -2, -3},
  //                          { 4,  5,  6}})->cast<Scalar>();
  //      CHECK_THROWS(Graph(CwiseProdAdd(a, b, c)).forward());
  //    }
  //    SECTION("Incorrect rows") {
  //      auto b = Values<1>({-1,
  //                          -2})->cast<Scalar>();
  //      auto c = Values<1>({4,
  //                          5})->cast<Scalar>();
  //      CHECK_THROWS(Graph(CwiseProdAdd(a, b, c)).forward());
  //    }
  //    SECTION("Rank 0") {
  //      auto b = Values<0>(-1)->cast<Scalar>();
  //      auto c = Values<0>(4)->cast<Scalar>();
  //      CHECK_THROWS(Graph(CwiseProdAdd(a, b, c)).forward());
  //    }
  //  }
  }

  //SECTION("CwiseMax") {
  //  check(CwiseMax(b, c), a);
  //  // Warning: CwiseMax does not have derivative at points where argmax is
  //  // more than one. Gradcheck might fail if two maxes are within gradcheck eps.
  //  CHECK_(CwiseMax(a, b, c), {a, b, c}, true, 1e-6);
  //}
}



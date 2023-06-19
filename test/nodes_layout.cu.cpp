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

#include <ginn/node/affine.h>
#include <ginn/node/common.h>
// #include <ginn/node/compare.h>
// #include <ginn/node/inplace.h>
// #include <ginn/node/layernorm.h>
#include <ginn/node/layout.h>
// #include <ginn/node/nlnode.h>
// #include <ginn/node/pick.h>
// #include <ginn/node/prod.h>
// #include <ginn/node/reduce.h>
// #include <ginn/node/select.h>
// #include <ginn/node/weight.h>

#include "check_node.h"
#include "testutil.h"

using namespace ginn;

// clang-format off

TEMPLATE_TEST_CASE("Dim", "[layout]", Real, Int, Half, void) {
  BaseNodePtr x;
  if constexpr(std::is_same_v<TestType, void>) {
    x = Random({3, 2, 1});
  } else {
    x = Random<TestType>({3, 2, 1});
  }
  auto d0 = Dim(x, 0);
  auto d1 = Dim(x, 1);
  auto d2 = Dim(x, 2);
  SECTION("Basic") {
    Graph(d0).forward();
    Graph(d1).forward();
    Graph(d2).forward();
    CHECK(d0->value() == 3);
    CHECK(d1->value() == 2);
    CHECK(d2->value() == 1);
  }
}

TEMPLATE_TEST_CASE("Stack", "[forward] [layout]", Real, Int, Half) {
  using Scalar = TestType;

  DataPtr<Scalar> a, b, c, d, e, f, expected;

  SECTION("Rank 1") {
    a = Values<1>({ 1,  2,  3,  4})->cast<Scalar>();
    b = Values<1>({ 5,  6,  7,  8})->cast<Scalar>();
    c = Values<1>({ 9, 10, 11, 12})->cast<Scalar>();
    d = Values<1>({13, 14, 15, 16})->cast<Scalar>();
    e = Values<1>({17, 18, 19, 20})->cast<Scalar>();
    f = Values<1>({21, 22, 23, 24})->cast<Scalar>();

    expected = Values<3>({{{1, 5}, {9,  13}, {17, 21}},
                          {{2, 6}, {10, 14}, {18, 22}},
                          {{3, 7}, {11, 15}, {19, 23}},
                          {{4, 8}, {12, 16}, {20, 24}}})->cast<Scalar>();
  }

  SECTION("Rank 2") {
    a = Values<2>({{ 1,  2}, { 3,  4}})->cast<Scalar>();
    b = Values<2>({{ 5,  6}, { 7,  8}})->cast<Scalar>();
    c = Values<2>({{ 9, 10}, {11, 12}})->cast<Scalar>();
    d = Values<2>({{13, 14}, {15, 16}})->cast<Scalar>();
    e = Values<2>({{17, 18}, {19, 20}})->cast<Scalar>();
    f = Values<2>({{21, 22}, {23, 24}})->cast<Scalar>();

    expected = Values<4>({{{{1, 5}, {9,  13}, {17, 21}},
                           {{2, 6}, {10, 14}, {18, 22}}},
                          {{{3, 7}, {11, 15}, {19, 23}},
                           {{4, 8}, {12, 16}, {20, 24}}}})->cast<Scalar>();
  }

  check(Stack({{a, b}, {c, d}, {e, f}}), expected);

#ifdef GINN_ENABLE_GPU
  if constexpr(ginn::is_floating_point_v<Scalar>) {
    auto eps = std::is_same_v<Scalar, Half> ? 2e-2 : 1e-4;
    for (auto& x : {a, b, c, d, e, f}) {
      x->value() = x->value().t() * Raw<Scalar>(0.1);
    }
    auto [a_, b_, c_, d_, e_, f_] = to_gpu(a, b, c, d, e, f);
    compare_devices(Stack({{a,  b }}),                     {a,  b, }, 
                    Stack({{a_, b_}}),                     {a_, b_,});
    compare_devices(Stack({{a,  b }, {c,  d }}),           {a,  b,  c,  d, }, 
                    Stack({{a_, b_}, {c_, d_}}),           {a_, b_, c_, d_,});
    compare_devices(Stack({{a,  b }, {c,  d }, {e,  f }}), {a,  b,  c,  d,  e,  f }, 
                    Stack({{a_, b_}, {c_, d_}, {e_, f_}}), {a_, b_, c_, d_, e_, f_});
    compare_devices(Stack({{a,  b }, {a,  b }}),           {a,  b,}, 
                    Stack({{a_, b_}, {a_, b_}}),           {a_, b_});
    compare_devices(Stack({{a,  a }, {a,  a }, {a,  a }}), {a, }, 
                    Stack({{a_, a_}, {a_, a_}, {a_, a_}}), {a_,}, eps);
  }
#else
  if constexpr (std::is_same_v<Scalar, Real>) {
    check_grad(Stack({{a, b}}),                 {a, b}            );
    check_grad(Stack({{a, b}, {c, d}}),         {a, b, c, d}      );
    check_grad(Stack({{a, b}, {c, d}, {e, f}}), {a, b, c, d, e, f});
    check_grad(Stack({{a, b}, {a, b}}),         {a, b}            );
    check_grad(Stack({{a, a}, {a, a}, {a, a}}), {a}               );
  }
#endif
}

TEMPLATE_TEST_CASE("Stack errors", "[forward] [layout]", Real, Int, Half) {
  using Scalar = TestType;

  auto a = Values<1>({ 1,  2,  3,  4})->cast<Scalar>();
  auto b = Values<1>({ 5,  6,  7,  8})->cast<Scalar>();
  auto c = Values<1>({ 9, 10, 11, 12})->cast<Scalar>();
  auto d = Values<1>({13, 14, 15, 16})->cast<Scalar>();
  auto e = Values<1>({17, 18, 19})->cast<Scalar>();
  auto f = Values<1>({21, 22, 23, 24})->cast<Scalar>();

  CHECK_THROWS(Stack({{a, b}, {c, d}, {e, f}})->forward());
  CHECK_THROWS(Stack({{a, b}, {c, d}, {f}})->forward());
  CHECK_THROWS(Stack(std::vector<std::vector<NodePtr<Scalar, CPU>>>{})->forward());
  CHECK_THROWS(Stack(std::vector<std::vector<NodePtr<Scalar, CPU>>>{{}})->forward());
}

TEMPLATE_TEST_CASE("Cat", "[forward] [layout]", Real, Int, Half) {
  using Scalar = TestType;
  auto Vals = [](NestedInitList<2, Int> vals) {
    return Values<2, Int>(vals)->template cast<Scalar>();
  };

  auto a = Vals({{1, 2}});
  auto b = Vals({{3, 4},
                 {5, 6}});
  auto c = Vals({{7, 8},
                 {9, 0}});

  auto res = Vals({{1, 2},
                   {3, 4},
                   {5, 6},
                   {7, 8},
                   {9, 0}});

  check(Cat(a, b, c), res);
#ifdef GINN_ENABLE_GPU
  if constexpr(std::is_floating_point_v<Scalar>) {
    auto [a_, b_, c_] = to_gpu(a, b, c);
    compare_devices(Cat(a,  b,  c ), {a,  b,  c },
                    Cat(a_, b_, c_), {a_, b_, c_}); 
    compare_devices(Cat(a,  b,  a ), {a,  b },
                    Cat(a_, b_, a_), {a_, b_}); 
    compare_devices(Cat(a,  b ), {a,  b },
                    Cat(a_, b_), {a_, b_}); 
    compare_devices(Cat(a,  a,  a ), {a },
                    Cat(a_, a_, a_), {a_}); 
  }
#else
  if constexpr(std::is_same_v<Scalar, Real>) {
    check_grad(Cat(a, b, c), {a, b, c}, true);
    check_grad(Cat(a, b, a), {a, b},    true);
    check_grad(Cat(a, b),    {a, b},    true);
    check_grad(Cat(a, a, a), {a},       true);
  }
#endif
}

TEMPLATE_TEST_CASE("RowwiseCat", "[layout]", Real, Int, Half) {
  using Scalar = TestType;

  auto Vals = [](NestedInitList<2, Int> vals) {
    return Values<2, Int>(vals)->template cast<Scalar>();
  };
  auto a = Vals({{1},
                 {2}});
  auto b = Vals({{3, 4},
                 {5, 6}});
  auto c = Vals({{7, 8, 9},
                 {0, 1, 2}});

  SECTION("Forward") {
    auto cat = RowwiseCat(a, b, c);

    auto res = Vals({{1, 3, 4, 7, 8, 9},
                     {2, 5, 6, 0, 1, 2}});

    check(cat, res);
    CHECK(cat->offsets() == std::vector<Size>{0, 1, 3});
    CHECK(cat->extents() == std::vector<Size>{1, 2, 3});

    //auto m = cat + Scalar(1);
    //auto uncat0 = RowwiseUncat(m, 0, cat);
    //auto uncat1 = RowwiseUncat(m, 1, cat);
    //auto uncat2 = RowwiseUncat(m, 2, cat);

    //auto a_ = Vals({{2},
    //                {3}});
    //auto b_ = Vals({{4, 5},
    //                {6, 7}});
    //auto c_ = Vals({{8, 9, 10},
    //                {1, 2,  3}});

    //check(uncat0, a_);
    //check(uncat1, b_);
    //check(uncat2, c_);
  }

  SECTION("Grad or cuda") {
#ifndef GINN_ENABLE_GPU
    if constexpr(std::is_same_v<Scalar, Real>) {
      check_grad(RowwiseCat(a, b, c), {a, b, c}, true);
    }
#else
    if constexpr(ginn::is_floating_point_v<Scalar>) {
      auto [a_, b_, c_] = to_gpu(a, b, c);
      compare_devices(RowwiseCat(a , b , c ), {a , b , c },
                      RowwiseCat(a_, b_, c_), {a_, b_, c_});
    }
#endif
    //for (size_t i = 0; i < 3; i++) {
    //  check_expr([&]() {
    //    auto cat = RowwiseCat(a, b, c);
    //    return RowwiseUncat(cat + 1, i, cat);
    //  }, {a, b, c}, true);
    //}
  }
}

TEMPLATE_TEST_CASE("Reshape", "[layout]", Real, Half, Int) {
  using Scalar = TestType;
  auto W = Values<2>({{1, 2, 3, 4, 5, 6}})->cast<Scalar>();

  SECTION("Forward") {
    auto col = Values<2>({{1}, {2}, {3}, {4}, {5}, {6}})->cast<Scalar>();
    auto mat = Values<2>({{1, 4},
                          {2, 5},
                          {3, 6}})->cast<Scalar>();


    check(Reshape(W, Shape{6, 1}), col);
    check(Reshape(W, Shape{3, 2}), mat);
  }
  
  std::vector<Shape> shapes{Shape{6, 1},
                            Shape{3, 2},
                            Shape{2, 3},
                            Shape{6},
                            Shape{3, 1, 2}};

#ifndef GINN_ENABLE_GPU
    if constexpr(std::is_same_v<Scalar, Real>) {
      for (auto&& s : shapes) { check_grad(Reshape(W, s), {W}, true); }
    }
#else
    if constexpr(ginn::is_floating_point_v<Scalar>) {
      auto W_ = W->copy_to(gpu());
      for (auto&& s : shapes) {
        compare_devices(Reshape(W,  s), {W},
                        Reshape(W_, s), {W_});
      }
    }
#endif
}

TEMPLATE_TEST_CASE("RankView", "[layout]", Real, Half, Int) {
  using Scalar = TestType;
  auto W = Values<2>({{1, 4},
                      {2, 5},
                      {3, 6}})->cast<Scalar>();

  SECTION("Forward") {
    auto col = Values<1>({1, 2, 3, 4, 5, 6})->cast<Scalar>();
    auto mat = Values<2>({{1, 4},
                          {2, 5},
                          {3, 6}})->cast<Scalar>();
    auto ten = Values<3>({{{1}, {4}},
                          {{2}, {5}},
                          {{3}, {6}}})->cast<Scalar>();

    check(RankView(W, 1), col);
    check(RankView(W, 2), mat);
    check(RankView(W, 3), ten);
  }

  SECTION("Grad or cuda") {
#ifndef GINN_ENABLE_GPU
    if constexpr(std::is_same_v<Scalar, Real>) {
      for (auto r : {1, 2, 3}) {
        check_grad(RankView(W, r), {W}, true);
      }
    }
#else
    if constexpr(ginn::is_floating_point_v<Scalar>) {
      auto W_ = W->copy_to(gpu());
      for (auto r : {1, 2, 3}) {
        compare_devices(RankView(W,  r), {W },
                        RankView(W_, r), {W_});
      }
    }
#endif
  }
}

TEMPLATE_TEST_CASE("Slice", "[layout]", Real, Half, Int) {
  using Scalar = TestType;
  auto x = Values<2>({{1, 2},
                      {3, 4},
                      {5, 6},
                      {7, 8}})->cast<Scalar>();

  SECTION("Row subset") {
    auto out = Values<2>({{3, 4},
                          {5, 6},
                          {7, 8}})->cast<Scalar>();
    check(Slice(x, Shape{1, 0}, Shape{3, 2}), out);
  }

  SECTION("Col subset") {
    auto out = Values<2>({{2},
                          {4},
                          {6},
                          {8}})->cast<Scalar>();
    check(Slice(x, Shape{0, 1}, Shape{4, 1}), out);
  }

  SECTION("Row & col subset") {
    auto out = Values<2>({{5},
                          {7}})->cast<Scalar>();
    check(Slice(x, Shape{2, 0}, Shape{2, 1}), out);
  }

#ifndef GINN_ENABLE_GPU
  if constexpr (std::is_same_v<Scalar, Real>) {
    check_grad(Slice(x, Shape{1, 0}, Shape{3, 2}), {x}, true);
    check_grad(Slice(x, Shape{0, 1}, Shape{4, 1}), {x}, true);
    check_grad(Slice(x, Shape{2, 0}, Shape{2, 1}), {x}, true);
  }
#else
  if constexpr (ginn::is_floating_point_v<Scalar>) {
    auto x_ = x->copy_to(gpu());
    compare_devices(Slice(x , Shape{1, 0}, Shape{3, 2}), {x },
                    Slice(x_, Shape{1, 0}, Shape{3, 2}), {x_});
    compare_devices(Slice(x , Shape{0, 1}, Shape{4, 1}), {x },
                    Slice(x_, Shape{0, 1}, Shape{4, 1}), {x_});
    compare_devices(Slice(x , Shape{2, 0}, Shape{2, 1}), {x },
                    Slice(x_, Shape{2, 0}, Shape{2, 1}), {x_});
  }
#endif
}

TEMPLATE_TEST_CASE("Chip", "[layout]", Real, Int, Half) {
  using Scalar = TestType;
  auto x = Values<2>({{1, 2},
                      {3, 4},
                      {5, 6},
                      {7, 8}})->cast<Scalar>();
  auto y = Values<1>({5, 6})->cast<Scalar>();
  auto z = Values<1>({2, 4, 6, 8})->cast<Scalar>();

  SECTION("Forward") {
    check(Chip(x, 2, 0), y);
    check(Chip(x, 1, 1), z);
  }

  SECTION("Grad or cuda") {
    using T = std::initializer_list<std::pair<int, int>>;

    SECTION("Basic") {
#ifndef GINN_ENABLE_GPU
      if constexpr (std::is_same_v<Scalar, Real>) {
        for (auto [offset, dim] : T{{0, 0}, {1, 1}, {2, 0}}) {
          check_grad(Chip(x, offset, dim), {x}, true);
        }
      }
#else
      if constexpr (ginn::is_floating_point_v<Scalar>) {
        auto x_ = x->copy_to(gpu());
        for (auto [offset, dim] : T{{0, 0}, {1, 1}, {2, 0}}) {
          compare_devices(Chip(x,  offset, dim), {x },
                          Chip(x_, offset, dim), {x_});
        }
      }
#endif
    }

    SECTION("High rank") {
      auto x = Random(cpu(), {4, 2, 3})->cast<Scalar>();
#ifndef GINN_ENABLE_GPU
      if constexpr (std::is_same_v<Scalar, Real>) {
        for (auto [offset, dim] : T{{3, 0}, {0, 1}, {1, 2}, {2, 2}}) {
          check_grad(Chip(x, offset, dim), {x}, true);
        }
      }
#else
      if constexpr (ginn::is_floating_point_v<Scalar>) {
        auto x_ = x->copy_to(gpu());
        for (auto [offset, dim] : T{{3, 0}, {0, 1}, {1, 2}, {2, 2}}) {
          compare_devices(Chip(x,  offset, dim), {x },
                          Chip(x_, offset, dim), {x_});
        }
      }
#endif
    }
  }
}

TEMPLATE_TEST_CASE("Permute", "[layout]", Real, Half, Int) {
  using Scalar = TestType;

  auto a = Values<3>({{{ 1,  2,  3,  4}, { 5,  6,  7,  8}},
                      {{ 9, 10, 11, 12}, {13, 14, 15, 16}},
                      {{17, 18, 19, 20}, {21, 22, 23, 24}}})->cast<Scalar>();
  CHECK(a->shape() == Shape{3, 2, 4});

  auto b = Values<3>({{{ 1,  5}, { 2,  6}, { 3,  7}, { 4,  8}},
                      {{ 9, 13}, {10, 14}, {11, 15}, {12, 16}},
                      {{17, 21}, {18, 22}, {19, 23}, {20, 24}}})->cast<Scalar>();
  auto c = Values<3>({{{ 1,  9, 17}, { 5, 13, 21}},
                      {{ 2, 10, 18}, { 6, 14, 22}},
                      {{ 3, 11, 19}, { 7, 15, 23}},
                      {{ 4, 12, 20}, { 8, 16, 24}}})->cast<Scalar>();
  auto d = Values<3>({{{ 1,  2,  3,  4}, { 9, 10, 11, 12}, {17, 18, 19, 20}},
                      {{ 5,  6,  7,  8}, {13, 14, 15, 16}, {21, 22, 23, 24}}})
                    ->cast<Scalar>();
  auto e = Values<3>({{{ 1,  9, 17}, { 2, 10, 18}, { 3, 11, 19}, { 4, 12, 20}},
                      {{ 5, 13, 21}, { 6, 14, 22}, { 7, 15, 23}, { 8, 16, 24}}})
                    ->cast<Scalar>();
  auto f = Values<3>({{{ 1,  5}, { 9, 13}, {17, 21}},
                      {{ 2,  6}, {10, 14}, {18, 22}},
                      {{ 3,  7}, {11, 15}, {19, 23}},
                      {{ 4,  8}, {12, 16}, {20, 24}}})->cast<Scalar>();

  //bool inplace = GENERATE(false, true);

  auto permute = [&] (auto&& x, const Shape& s) {
    //return inplace ? InPlacePermute(x * 1, s) : Permute(x, s);
    return Permute(x, s);
  };


  check(permute(a, Shape{0, 2, 1}), b);
  check(Transpose(a, 1, 2),         b);
  check(permute(a, Shape{2, 1, 0}), c);
  check(Transpose(a, 2, 0),         c);
  check(permute(a, Shape{1, 0, 2}), d);
  check(Transpose(a, 0, 1),         d);
  check(permute(a, Shape{1, 2, 0}), e);
  check(permute(a, Shape{2, 0, 1}), f);
  check(permute(a, Shape{0, 1, 2}), a);

  std::vector<Shape> shapes{{0, 2, 1},
                            {2, 1, 0},
                            {1, 0, 2},
                            {1, 2, 0},
                            {2, 0, 1},
                            {0, 1, 2}};
  std::vector<std::pair<int, int>> indices{{0, 1},
                                           {1, 0},
                                           {0, 2},
                                           {2, 0},
                                           {1, 2},
                                           {2, 1}};

#ifndef GINN_ENABLE_GPU
  if constexpr (std::is_same_v<Scalar, Real>) {
    for (auto&& s : shapes)     { check_grad(permute(a, s),      {a}, true); }
    for (auto [i, j] : indices) { check_grad(Transpose(a, i, j), {a}, true); }
  }
#else
  if constexpr (ginn::is_floating_point_v<Scalar>) {
    auto a_ = a->copy_to(gpu());
    for (auto&& s : shapes)     {
      compare_devices(permute(a,  s), {a },
                      permute(a_, s), {a_});
    }
    for (auto [i, j] : indices) {
      compare_devices(Transpose(a,  i, j), {a },
                      Transpose(a_, i, j), {a_});
    }
  }
#endif
}


TEMPLATE_TEST_CASE("Broadcast", "[layout]", Real, Half, Int) {
  using Scalar = TestType;
  auto a = Values<2>({{1},
                      {2},
                      {3}})->cast<Scalar>();
  auto b = Values<2>({{0.1, 1.2, 2.3}})->cast<Scalar>();

  REQUIRE(a->shape() == Shape{3, 1});
  REQUIRE(b->shape() == Shape{1, 3});

  SECTION("RowBroadcast") {
    auto b3 = Values<2>({{0.1, 1.2, 2.3},
                         {0.1, 1.2, 2.3},
                         {0.1, 1.2, 2.3}})->cast<Scalar>();

    check(RowBroadcast(b, 3        ), b3);
    check(RowBroadcast(b, 1        ), b );
    check(RowBroadcast(b, Dim(a, 0)), b3);
    check(RowBroadcast(b, Dim(a, 1)), b );
#ifndef GINN_ENABLE_GPU
    if constexpr(std::is_same_v<Scalar, Real>) {
      check_grad(RowBroadcast(b, 3        ), {b}, true);
      check_grad(RowBroadcast(b, 1        ), {b}, true);
      check_grad(RowBroadcast(b, Dim(a, 0)), {b}, true);
      check_grad(RowBroadcast(b, Dim(a, 1)), {b}, true);
    }
#else
    if constexpr(ginn::is_floating_point_v<Scalar>) {
      auto b_ = b->copy_to(gpu());
      compare_devices(RowBroadcast(b,  3        ), {b },
                      RowBroadcast(b_, 3        ), {b_});
      compare_devices(RowBroadcast(b,  1        ), {b },
                      RowBroadcast(b_, 1        ), {b_});
      compare_devices(RowBroadcast(b,  Dim(a, 0)), {b },
                      RowBroadcast(b_, Dim(a, 0)), {b_});
      compare_devices(RowBroadcast(b,  Dim(a, 1)), {b },
                      RowBroadcast(b_, Dim(a, 1)), {b_});
    }
#endif
  }

  SECTION("ColBroadcast") {
    auto a3 = Values<2>({{1, 1, 1},
                         {2, 2, 2},
                         {3, 3, 3}})->cast<Scalar>();

    check(ColBroadcast(a, 3        ), a3);
    check(ColBroadcast(a, 1        ), a );
    check(ColBroadcast(a, Dim(b, 1)), a3);
    check(ColBroadcast(a, Dim(b, 0)), a );
#ifndef GINN_ENABLE_GPU
    if constexpr(std::is_same_v<Scalar, Real>) {
      check_grad(ColBroadcast(a, 3        ), {a}, true);
      check_grad(ColBroadcast(a, 1        ), {a}, true);
      check_grad(ColBroadcast(a, Dim(b, 0)), {a}, true);
      check_grad(ColBroadcast(a, Dim(b, 1)), {a}, true);
    }
#else
    if constexpr(ginn::is_floating_point_v<Scalar>) {
      auto a_ = a->copy_to(gpu());
      compare_devices(ColBroadcast(a,  3        ), {a },
                      ColBroadcast(a_, 3        ), {a_});
      compare_devices(ColBroadcast(a,  1        ), {a },
                      ColBroadcast(a_, 1        ), {a_});
      compare_devices(ColBroadcast(a,  Dim(b, 0)), {a },
                      ColBroadcast(a_, Dim(b, 0)), {a_});
      compare_devices(ColBroadcast(a,  Dim(b, 1)), {a },
                      ColBroadcast(a_, Dim(b, 1)), {a_});
    }
#endif
  }
}

TEMPLATE_TEST_CASE("UpperTri", "[layout]", Real, Int) {
  using Scalar = TestType;
  auto tri2 = Values<2>({{1, 1},
                         {0, 1}})->cast<Scalar>();
  auto tri5 = Values<2>({{1, 1, 1, 1, 1},
                         {0, 1, 1, 1, 1},
                         {0, 0, 1, 1, 1},
                         {0, 0, 0, 1, 1},
                         {0, 0, 0, 0, 1}})->cast<Scalar>();

  check(UpperTri<Scalar>(cpu(), 2), tri2);
  check(UpperTri<Scalar>(cpu(), 5), tri5);

#ifdef GINN_ENABLE_GPU
  check(UpperTri<Scalar>(gpu(), 5), tri5->copy_to(gpu()));
#endif
}
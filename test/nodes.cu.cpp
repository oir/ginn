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
#include <ginn/node/nlnode.h>
// #include <ginn/node/pick.h>
// #include <ginn/node/prod.h>
// #include <ginn/node/reduce.h>
// #include <ginn/node/select.h>
// #include <ginn/node/weight.h>

#include "check_node.h"
#include "testutil.h"

using namespace ginn;

#ifdef GINN_ENABLE_GPU
constexpr bool gpu_enabled = true;
#else
constexpr bool gpu_enabled = false;
#endif

// clang-format off

using Typelist = std::tuple<
#ifdef GINN_ENABLE_GPU
    Tensor<Real, GPU>,
    Tensor<Half, GPU>,
#endif
    Tensor<Real, CPU>,
    Tensor<Half, CPU>
>;


TEMPLATE_LIST_TEST_CASE("Weight", "[weight]", Typelist) {
  using Scalar = typename TestType::Scalar;
  constexpr auto Kind = TestType::device_kind;

  auto W = Weight<Scalar>(default_dev<Kind>(), {2, 3});
  W->set_random();
  auto t = W->value();

  CHECK(W->forwarded);
  W->reset_forwarded();
  CHECK(W->forwarded);

  W->forward();
  CHECK(W->value() == t);

  W->reset_grad();

  auto W2 = W->copy(Copy::Tied);
  CHECK(&W2->value() == &W->value());
  CHECK(&W2->grad()  != &W->grad() );

  auto W3 = W->copy(Copy::Deep);
  CHECK(W3->value()  == W->value() );
  CHECK(&W3->value() != &W->value());
  CHECK(&W3->grad()  != &W->grad() );

  auto W4 = Weight(*W); // use copy ctor, should deep copy
  CHECK(W4->value()  == W->value() );
  CHECK(&W4->value() != &W->value());
  CHECK(&W4->grad()  != &W->grad() );
}

TEMPLATE_TEST_CASE("Nonlin", "[nlnode]", Real, Half) {
  using Scalar = TestType;
  auto W = Values<2>({{-1, -2, -3},
                      { 4,  5,  6}})->cast<Scalar>();
  auto tanhW = Values<2>({{-0.76159415, -0.96402758, -0.99505475},
                          { 0.99932929,  0.99990920,  0.99998771}})->cast<Scalar>();
  auto reluW = Values<2>({{0, 0, 0},
                          {4, 5, 6}})->cast<Scalar>();
  auto sigmW = Values<2>({{0.26894142, 0.11920292, 0.04742587},
                          {0.98201379, 0.99330714, 0.99752737}})->cast<Scalar>();
  auto smaxW = Values<2>({{0.00669285, 9.11051194e-04, 1.23394576e-04},
                          {0.99330715, 9.99088949e-01, 9.99876605e-01}})->cast<Scalar>();
  auto absW  = Values<2>({{1, 2, 3},
                          {4, 5, 6}})->cast<Scalar>();
  auto logaW = Values<2>({{0,          0.69314718, 1.09861229},
                          {1.38629436, 1.60943791, 1.79175947}})->cast<Scalar>();

  check(Identity(W), W    );
  check(Tanh(W),     tanhW);
  check(Relu(W),     reluW);
  check(Sigmoid(W),  sigmW, std::is_same_v<Scalar, Half> ? 1e-3 : 1e-6); // TODO: how can i make this more accurate?
  check(Softmax(W),  smaxW, std::is_same_v<Scalar, Half> ? 1e-3 : 1e-6); // TODO: how can i make this more accurate?
  check(Sqrt(CwiseProd(W, W)), absW);
  CHECK_THROWS(check(Sqrt(W), W));
  check(Log(absW),   logaW);
  // TODO: Gelu forward
  // TODO: Gelu2 forward

  if constexpr (not gpu_enabled and std::is_same_v<Scalar, Real>) {
    check_grad(Identity(W), {W}, true);
    check_grad(Tanh(W),     {W}, true);
    check_grad(Relu(W),     {W}, true);
    check_grad(Sigmoid(W),  {W}, true);
    check_grad(Softmax(W),  {W}, true);
    check_grad(Sqrt(W + 3),  {W}, true);
    check_grad(Log(W + 1.5), {W}, true);
    check_grad(Gelu(W),     {W}, true);
    check_grad(Gelu2(W),    {W}, true);
  }
  if constexpr (gpu_enabled and ginn::is_floating_point_v<Scalar>) {
    auto [W_] = to_gpu(W);
    auto eps = std::is_same_v<Scalar, Half> ? 1e-3 : 1e-4;
    SECTION("Id")      { compare_devices(Identity(W),   {W}, Identity(W_),   {W_}); }
    SECTION("Tanh")    { compare_devices(Tanh(W * 0.1), {W}, Tanh(W_ * 0.1), {W_}); }
    SECTION("Relu")    { compare_devices(Relu(W),       {W}, Relu(W_),       {W_}); }
    SECTION("Sigmoid") { compare_devices(Sigmoid(W),    {W}, Sigmoid(W_),    {W_}); }
    SECTION("Softmax") { compare_devices(Softmax(W * 0.1), {W}, Softmax(W_ * 0.1), {W_}); }
    SECTION("Sqrt")    { compare_devices(Sqrt(W + 3),   {W}, Sqrt(W_ + 3),  {W_}); }
    SECTION("Log")     { compare_devices(Log(W + 3.5),  {W}, Log(W_ + 3.5), {W_}); }
    SECTION("Gelu")    { compare_devices(Gelu(W),       {W}, Gelu(W_),      {W_}); }
    SECTION("Gelu2")   { compare_devices(Gelu2(W),      {W}, Gelu2(W_),     {W_}, eps); }
  }
}

TEMPLATE_TEST_CASE("Nonlin Extreme", "[nlnode]", Real, Half) {
  using Scalar = TestType;
  auto x = Values<2>({{10000.}, {-10000.}})->cast<Scalar>();
  auto x2 = Values<2>({{5.}, {-std::numeric_limits<Real>::infinity()}})->cast<Scalar>();

  REQUIRE(x->shape() == Shape{2, 1});

  auto tanhx    = Values<2>({{1.}, {-1.}})->cast<Scalar>();
  auto sigmoidx = Values<2>({{1.}, {0.}})->cast<Scalar>();
  auto smaxx    = Values<2>({{1.}, {0.}})->cast<Scalar>();
  auto smaxx2   = Values<2>({{1., 1.}})->cast<Scalar>();

  REQUIRE(smaxx2->shape() == Shape{1, 2});

  check(Tanh(x),     tanhx   );
  check(Sigmoid(x),  sigmoidx);
  check(Softmax(x),  smaxx);
  check(Softmax(x2), smaxx);
  check(Softmax(Reshape(x, Shape{1, 2})), smaxx2  );

  if constexpr (not gpu_enabled and std::is_same_v<Scalar, Real>) {
    check_grad(Tanh(x),     {x});
    check_grad(Sigmoid(x),  {x});
    check_grad(Softmax(x),  {x});
    check_grad(Softmax(x2), {x2});
    check_grad(Softmax(Reshape(x, Shape{1, 2})), {x});
  }
  if constexpr (gpu_enabled and ginn::is_floating_point_v<Scalar>) {
    auto [x_, x2_] = to_gpu(x, x2);
    compare_devices(Tanh(x),     {x }, Tanh(x_),     {x_ });
    compare_devices(Sigmoid(x),  {x }, Sigmoid(x_),  {x_ });
    compare_devices(Softmax(x),  {x }, Softmax(x_),  {x_ });
    compare_devices(Softmax(x2), {x2}, Softmax(x2_), {x2_});
    compare_devices(Softmax(Reshape(x, Shape{1, 2})), {x},
                    Softmax(Reshape(x_, Shape{1, 2})), {x_});
  }
}
//
//TEMPLATE_TEST_CASE("Pickles", "[pick][nlnode]", Real, Half) {
//  using Scalar = TestType;
//  auto W = Values<2>({{-0.5,  0.55, -0.45},
//                      { 1. ,  2.  , -1.  },
//                      { 0. ,  0.  ,  0.  },
//                      { 0.3, -0.33,  1.3 }})->cast<Scalar>();
//  //auto sm = Values<2>({{0.106884, 0.159876,  0.112361},
//  //                     {0.47902,  0.68157,   0.0648268},
//  //                     {0.176222, 0.0922404, 0.176218},
//  //                     {0.237874, 0.0663138, 0.646594}});
//  auto p     = Values<2>({{0.3, 0.55, -1.}})->cast<Scalar>();
//  auto psm   = Values<2>({{0.23787436, 0.15987601, 0.06482681}})->cast<Scalar>();
//  auto pnlsm = Values<2>({{1.43601264, 1.8333567,  2.73603603}})->cast<Scalar>();
//
//  auto iv = std::vector<Int>{3, 0, 1};
//  auto it = Values<1>({3, 0, 1})->cast<Int>();
//  it->set_has_grad(false);
//
//  SECTION("Pick") {
//    check(Pick(W, iv), p);
//    check(Pick(W, it), p);
//    CHECK_(Pick(W, iv), {W},     true);
//    CHECK_(Pick(W, it), {W, it}, true);
//  }
//  SECTION("PickSoftmax") {
//    check(PickSoftmax(W, iv),   psm, std::is_same_v<Scalar, Half> ? 1e-3 : 1e-6);
//    check(PickSoftmax(W, it),   psm, std::is_same_v<Scalar, Half> ? 1e-3 : 1e-6);
//    check(Pick(Softmax(W), iv), psm, std::is_same_v<Scalar, Half> ? 1e-3 : 1e-6);
//    check(Pick(Softmax(W), it), psm, std::is_same_v<Scalar, Half> ? 1e-3 : 1e-6);
//    CHECK_(PickSoftmax(W, iv),   {W},     true);
//    CHECK_(PickSoftmax(W, it),   {W, it}, true);
//    CHECK_(Pick(Softmax(W), iv), {W},     true);
//    CHECK_(Pick(Softmax(W), it), {W, it}, true);
//  }
//  SECTION("PickNegLogSoftmax") {
//    check(PickNegLogSoftmax(W, iv),   pnlsm, std::is_same_v<Scalar, Half> ? 1e-3 : 1e-6);
//    check(PickNegLogSoftmax(W, it),   pnlsm, std::is_same_v<Scalar, Half> ? 1e-3 : 1e-6);
//    check(-Log(PickSoftmax(W, iv)),   pnlsm, std::is_same_v<Scalar, Half> ? 1e-3 : 1e-6);
//    check(-Log(PickSoftmax(W, it)),   pnlsm, std::is_same_v<Scalar, Half> ? 1e-3 : 1e-6);
//    check(Pick(-Log(Softmax(W)), iv), pnlsm, std::is_same_v<Scalar, Half> ? 1e-3 : 1e-6);
//    check(Pick(-Log(Softmax(W)), it), pnlsm, std::is_same_v<Scalar, Half> ? 1e-3 : 1e-6);
//    CHECK_(PickNegLogSoftmax(W, iv),   {W},     true);
//    CHECK_(PickNegLogSoftmax(W, it),   {W, it}, true);
//    CHECK_(-Log(PickSoftmax(W, iv)),   {W},     true);
//    CHECK_(-Log(PickSoftmax(W, it)),   {W, it}, true);
//    CHECK_(Pick(-Log(Softmax(W)), iv), {W},     true);
//    CHECK_(Pick(-Log(Softmax(W)), it), {W, it}, true);
//  }
//}
//
//TEMPLATE_TEST_CASE("PickNegLogSigmoid", "[pick][nlnode]", Real, Half) {
//  using Scalar = TestType;
//  auto W = Values<2>({{-0.5,  0.55, -0.45},
//                      { 1. ,  2.  , -1.  },
//                      { 0. ,  0.  ,  0.  },
//                      { 0.3, -0.33,  1.3 }})->cast<Scalar>();
//  auto p = Values<2>({{0, 1, 0},
//                      {1, 0, 1},
//                      {0, 1, 0},
//                      {1, 0, 1}})->cast<Int>();
//  p->set_has_grad(false);
//  auto pnls = Values<2>({{0.47407698, 0.45549248, 0.49324895},
//                         {0.31326169, 2.12692801, 1.31326169},
//                         {0.69314718, 0.69314718, 0.69314718},
//                         {0.55435524, 0.54169836, 0.24100845}})->cast<Scalar>();
//
//  check(PickNegLogSigmoid(W, p), pnls, std::is_same_v<Scalar, Half> ? 2e-3 : 1e-6);
//  CHECK_(PickNegLogSigmoid(W, p), {W, p}, true);
//}
//
//TEMPLATE_TEST_CASE("Select", "[select]", Real, Half, Int) {
//  using Scalar = TestType;
//  auto if_ = Values<2>({{1., 0.},
//                        {0., 1.},
//                        {1., 0.}})->cast<bool>();
//  if_->set_has_grad(false); // TODO: maybe integral nodes should have this default?
//  auto a = Values<2>({{1., 2.},
//                      {3., 4.},
//                      {5., 6.}})->cast<Scalar>();
//  auto b = Values<2>({{.1, .2},
//                      {.3, .4},
//                      {.5, .6}})->cast<Scalar>();
//
//  auto y1 = Values<2>({{1., .2},
//                       {.3, 4.},
//                       {5., .6}})->cast<Scalar>();
//  auto y2 = Values<2>({{1., 7.},
//                       {7., 4.},
//                       {5., 7.}})->cast<Scalar>();
//  auto y3 = Values<2>({{7., .2},
//                       {.3, 7.},
//                       {7., .6}})->cast<Scalar>();
//  auto y4 = Values<2>({{7., -2},
//                       {-2, 7.},
//                       {7., -2}})->cast<Scalar>();
//
//
//  check(Select(if_, a, b),                  y1);
//  check(Select(if_, a, Scalar(7)),          y2);
//  check(Select(if_, Scalar(7), b),          y3);
//  check(Select(if_, Scalar(7), Scalar(-2)), y4);
//  CHECK_(Select(if_, a, b),                  {if_, a, b});
//  CHECK_(Select(if_, a, Scalar(7)),          {if_, a});
//  CHECK_(Select(if_, Scalar(7), b),          {if_, b});
//  CHECK_(Select(if_, Scalar(7), Scalar(-2)), {if_});
//}
//
//TEMPLATE_TEST_CASE("Mask", "[select]", Real, Half, Int) {
//  using Scalar = TestType;
//  auto mask = Values<2>({{1., 0.},
//                         {0., 1.},
//                         {1., 0.}})->cast<Scalar>();
//  mask->set_has_grad(false);
//  auto mask2 = Values<2>({{1.},
//                          {0.},
//                          {1.}})->cast<Scalar>();
//  mask2->set_has_grad(false);
//  auto a = Values<2>({{1., 2.},
//                      {3., 4.},
//                      {5., 6.}})->cast<Scalar>();
//
//  SECTION("Forward") {
//    auto y1 = Values<2>({{ 1., -1.},
//                         {-1.,  4.},
//                         { 5., -1.}})->cast<Scalar>();
//    auto y2 = Values<2>({{1., 2.},
//                         {7., 7.},
//                         {5., 6.}})->cast<Scalar>();
//
//    check(Mask(a, mask,  Scalar(-1)), y1);
//    check(Mask(a, mask2, Scalar(7)),  y2);
//  }
//
//  SECTION("Grad or cuda") {
//    CHECK_(Mask(a, mask,  Scalar(-1)), {a, mask });
//    CHECK_(Mask(a, mask2, Scalar(7) ), {a, mask2});
//
//    auto W  = Random(Dev, {2, 3, 2})->cast<Scalar>();
//    auto m1 = Random(Dev, {2, 3, 2})->cast<Scalar>();
//    auto m2 = Random(Dev, {2, 3, 1})->cast<Scalar>();
//    auto m3 = Random(Dev, {2, 1, 1})->cast<Scalar>();
//
//    auto set_mask = [](auto& m) {
//      m->set_random();
//      m->value() = (m->value().t() > Scalar(0)).template cast<Scalar>();
//      m->set_has_grad(false);
//    };
//
//    set_mask(m1);
//    set_mask(m2);
//    set_mask(m3);
//
//    CHECK_(Mask(W, m1, Scalar( 3.)), {W, m1, m2, m3});
//    CHECK_(Mask(W, m2, Scalar(-3.)), {W, m1, m2, m3});
//    CHECK_(Mask(W, m3, Scalar( 0.)), {W, m1, m2, m3});
//  }
//}
//
//TEMPLATE_TEST_CASE("LayerNorm", "[layernorm][inplace]", Real, Half) {
//  // TODO: forward test
//  using Scalar = TestType;
//  auto x = Random(Dev, {3, 2})->cast<Scalar>();
//  auto y = Random(Dev, {3, 2, 4})->cast<Scalar>();
//  x->value() = x->value().t() * Scalar(3) + Scalar(2);
//  y->value() = y->value().t() * Scalar(2.5) - Scalar(2);
//
//  #ifdef GINN_ENABLE_GPU
//  auto eps2 = std::is_same_v<Scalar, Half> ? 2e-2 : 1e-4;
//  #else
//  auto eps2 = 1e-4;
//  #endif
//
//  CHECK_(LayerNorm(x), {x}, false, eps2);
//  CHECK_(LayerNorm(y), {y}, false, eps2);
//  CHECK_(InPlaceLayerNorm(1 * x), {x}, false, eps2);
//  CHECK_(InPlaceLayerNorm(1 * y), {y}, false, eps2);
//  //SECTION("Layer") {
//  //  auto ln1 = LayerNormLayer();
//  //  auto ln2 = LayerNormLayer(Dev, 3);
//  //  ln2->gamma->value().set_random();
//  //  ln2->gamma->value() = ln2->gamma->value().t() + Real(1);
//  //  ln2->beta->value().set_zero();
//  //  CHECK_(ln1->run(x), {x});
//  //  CHECK_(ln2->run(x), {x, ln2->gamma, ln2->beta});
//  //}
//}
//
//TEMPLATE_TEST_CASE("Sums", "[reduce]", Real, Half) {
//  using Scalar = TestType;
//  auto W = Values<2>({{1, 2, 3},
//                      {4, 5, 6}})->cast<Scalar>();
//  SECTION("Sum") {
//    auto Wsum = Values<0>(21)->cast<Scalar>();
//    check(Sum(W), Wsum);
//  }
//
//  SECTION("AxisSum") {
//    auto V    = Values<3>({{{1, 2, 3},
//                            {4, 5, 6}},
//                           {{.1, .2, .3},
//                            {.4, .5, .6}}})->cast<Scalar>();
//    auto V0   = Values<2>({{1.1, 2.2, 3.3},
//                           {4.4, 5.5, 6.6}})->cast<Scalar>();
//    auto V01  = Values<1>({5.5, 7.7, 9.9})->cast<Scalar>();
//    auto V012 = Values<0>(23.1)->cast<Scalar>();
//    auto V1   = Values<2>({{5 , 7 , 9 },
//                           {.5, .7, .9}})->cast<Scalar>();
//    auto V12  = Values<1>({21,
//                           2.1})->cast<Scalar>();
//    auto V2   = Values<2>({{ 6,
//                            15},
//                           {.6,
//                            1.5}})->cast<Scalar>();
//    auto V02  = Values<1>({ 6.6,
//                           16.5})->cast<Scalar>();
//
//    Real eps = std::is_same_v<Scalar, Half> ? 1e-3 : 1e-6;
//    check(AxisSum(V, {0}),       V0,   eps);
//    check(AxisSum(V, {0, 1}),    V01,  eps);
//    check(AxisSum(V, {0, 1, 2}), V012, eps);
//    check(AxisSum(V, {1}),       V1,   eps);
//    check(AxisSum(V, {1, 2}),    V12,  eps);
//    check(AxisSum(V, {2}),       V2,   eps);
//    check(AxisSum(V, {0, 2}),    V02,  eps);
//    CHECK_THROWS(AxisSum(V, {0, 0}));
//    CHECK_THROWS(AxisSum(V, {2, 0}));
//    CHECK_(AxisSum(V, {0}),       {V}, true);
//    CHECK_(AxisSum(V, {0, 1}),    {V}, true);
//    CHECK_(AxisSum(V, {0, 1, 2}), {V}, true);
//    CHECK_(AxisSum(V, {1}),       {V}, true);
//    CHECK_(AxisSum(V, {1, 2}),    {V}, true);
//    CHECK_(AxisSum(V, {2}),       {V}, true);
//    CHECK_(AxisSum(V, {0, 2}),    {V}, true);
//  }
//
//  SECTION("Mean") {
//    auto m = Values<0>(3.5)->cast<Scalar>();
//
//    check(Mean(W), m);
//    CHECK_(Mean(W), {W}, true);
//  }
//
//  SECTION("Variance") {
//    auto m = Values<0>(35./12.)->cast<Scalar>();
//
//    check(Variance(W), m);
//    CHECK_(Variance(W), {W}, true);
//  }
//}
//
//TEMPLATE_TEST_CASE("Comparison", "[compare]", Real, Half, Int) {
//  using Scalar = TestType;
//  auto a = Values<2>({{1.}, {2.}, {3.}, {4.}, {5.}})->cast<Scalar>();
//  auto b = Values<2>({{5.}, {4.}, {3.}, {2.}, {1.}})->cast<Scalar>();
//
//  REQUIRE(a->shape() == Shape{5, 1});
//  REQUIRE(b->shape() == Shape{5, 1});
//
//  auto y = Values<2>({{1.}, {1.}, {0.}, {0.}, {0.}})->cast<bool>();
//
//  SECTION("LessThan") {
//    check(LessThan(a, b), y);
//    check(a < b,          y);
//    CHECK_(LessThan(a, b), {a, b}, true);
//    CHECK_(a < b,          {a, b}, true);
//  }
//}
//
//TEMPLATE_TEST_CASE("Prod", "[prod]", Real, Half) {
//  using Scalar = TestType;
//  auto W = Values<2>({{1, 2, 3},
//                      {4, 5, 6}})->cast<Scalar>();
//  auto V = Values<2>({{ 0.6,  0.5},
//                      { 0.4, -0.1},
//                      {-0.2, -0.3}})->cast<Scalar>();
//
//  auto WV = Values<2>({{0.8, -0.6},
//                       {3.2, -0.3}})->cast<Scalar>();
//
//  Real eps = std::is_same_v<Scalar, Half> ? 1e-2 : 1e-6; // TODO: 😢
//  Real eps2 = std::is_same_v<Scalar, Half> ? 1e-2 : 1e-4;
//
//  check(Prod(W, V), WV, eps);
//  check(W * V,      WV, eps);
//  CHECK_(Prod(W, V), {W, V}, true, eps2);
//  CHECK_(W * V,      {W, V}, true, eps2);
//}
//
//TEMPLATE_TEST_CASE("BatchedProd", "[prod]", Real, Half) {
//  using Scalar = TestType;
//
//  SECTION("Basic") {
//    auto a = Random({2, 3, 4})->cast<Scalar>();
//    auto b = Random({3, 5, 4})->cast<Scalar>();
//    a->value() = a->value().t() + Scalar(1.);
//    b->value() = b->value().t() - Scalar(1.);
//    auto c = BatchedProd(a, b);
//
//    auto c0 = Chip(c, 0, 2);
//    auto c1 = Chip(c, 1, 2);
//    auto c2 = Chip(c, 2, 2);
//    auto c3 = Chip(c, 3, 2);
//
//    auto a0 = Chip(a, 0, 2), b0 = Chip(b, 0, 2);
//    auto a1 = Chip(a, 1, 2), b1 = Chip(b, 1, 2);
//    auto a2 = Chip(a, 2, 2), b2 = Chip(b, 2, 2);
//    auto a3 = Chip(a, 3, 2), b3 = Chip(b, 3, 2);
//
//    auto c0_ = a0 * b0;
//    auto c1_ = a1 * b1;
//    auto c2_ = a2 * b2;
//    auto c3_ = a3 * b3;
//
//    Real eps = std::is_same_v<Scalar, Half> ? 1e-2 : 1e-6; // TODO: 😢
//    Real eps2 = std::is_same_v<Scalar, Half> ? 1e-2 : 1e-4;
//
//    check(c0, c0_, eps);
//    check(c1, c1_, eps);
//    check(c2, c2_, eps);
//    check(c3, c3_, eps);
//
//    CHECK_(BatchedProd(a, b), {a, b}, false, eps2);
//  }
//
//  SECTION("High rank") {
//    auto a = Random({2, 3, 2, 2})->cast<Scalar>();
//    auto b = Random({3, 5, 2, 2})->cast<Scalar>();
//    a->value() = a->value().t() + Scalar(1.);
//    b->value() = b->value().t() - Scalar(1.);
//    auto c = BatchedProd(a, b);
//
//    auto ChipTwice = [](auto x, Size i, Size j) {
//      return Chip(Chip(x, j, 3), i, 2);
//    };
//
//    auto c00 = ChipTwice(c, 0, 0);
//    auto c01 = ChipTwice(c, 0, 1);
//    auto c10 = ChipTwice(c, 1, 0);
//    auto c11 = ChipTwice(c, 1, 1);
//
//    auto a00 = ChipTwice(a, 0, 0), b00 = ChipTwice(b, 0, 0);
//    auto a01 = ChipTwice(a, 0, 1), b01 = ChipTwice(b, 0, 1);
//    auto a10 = ChipTwice(a, 1, 0), b10 = ChipTwice(b, 1, 0);
//    auto a11 = ChipTwice(a, 1, 1), b11 = ChipTwice(b, 1, 1);
//
//    auto c00_ = a00 * b00;
//    auto c01_ = a01 * b01;
//    auto c10_ = a10 * b10;
//    auto c11_ = a11 * b11;
//
//    Real eps = std::is_same_v<Scalar, Half> ? 1e-2 : 1e-6; // TODO: 😢
//    Real eps2 = std::is_same_v<Scalar, Half> ? 1e-2 : 1e-4;
//
//    check(c00, c00_, eps);
//    check(c01, c01_, eps);
//    check(c10, c10_, eps);
//    check(c11, c11_, eps);
//
//    CHECK_(BatchedProd(a, b), {a, b}, false, eps2);
//  }
//}
//
TEMPLATE_TEST_CASE("Affine", "[affine]", Real, Half) {
  using Scalar = TestType;
  Real eps = std::is_same_v<Scalar, Half> ? 2e-3 : 1e-6; // TODO: 😢
#ifdef GINN_ENABLE_GPU
  Real eps2 = std::is_same_v<Scalar, Half> ? 5e-3 : 1e-4;
#endif

  auto W = Values<2>({{1, 2, 3},
                      {4, 5, 6}})->cast<Scalar>();
  auto V = Values<2>({{ 0.6},
                      { 0.4},
                      {-0.2}})->cast<Scalar>();
  auto b = Values<2>({{0.01},
                      {0.02}})->cast<Scalar>();

  SECTION("Affine")        {
    auto WVb = Values<2>({{0.81},
                          {3.22}})->cast<Scalar>();
    check(Affine(W, V, b), WVb, eps);
#ifdef GINN_ENABLE_GPU
    if constexpr (ginn::is_floating_point_v<Scalar>) {
      auto W_ = W->copy_to(gpu());
      auto V_ = V->copy_to(gpu());
      auto b_ = b->copy_to(gpu());
      compare_devices(Affine(W,  V,  b),  {W,  V,  b },
                      Affine(W_, V_, b_), {W_, V_, b_}, eps2);
    }
#else
    if constexpr (std::is_same_v<Scalar, Real>) {
      check_grad(Affine(W, V, b),  {W, V, b}, true);
    }
#endif
    //check(W * V + b,       WVb, eps);
    //CHECK_(Affine(W, V, b), {W, V, b}, true, eps2);
  }
  //SECTION("AffineSigmoid") {
  //  auto sigmWVb = Values<2>({{0.692109},
  //                            {0.96158 }})->cast<Scalar>();
  //  check(Affine(SigmoidOp<Scalar>(), W, V, b), sigmWVb, eps);
  //  check(Affine<SigmoidOp>(W, V, b),           sigmWVb, eps);
  //  CHECK_(Affine(SigmoidOp<Scalar>(), W, V, b), {W, V, b}, true, eps2);
  //  CHECK_(Affine<SigmoidOp>(W, V, b),           {W, V, b}, true, eps2);
  //}
  //SECTION("AffineSoftmax") {
  //  auto smaxWVb = Values<2>({{0.0824133},
  //                            {0.917587 }})->cast<Scalar>();
  //  check(Affine<SoftmaxOp>(W, V, b), smaxWVb, eps);
  //  CHECK_(Affine<SoftmaxOp>(W, V, b), {W, V, b}, true, eps2);
  //}

  //SECTION("Other nonlins") {
  //  CHECK_(Affine<TanhOp>(W, V, b), {W, V, b}, true, eps2);
  //  CHECK_(Affine<ReluOp>(W * 10, V, b), {W, V, b}, true, eps2);
  //  CHECK_(Affine<Gelu2Op>(W, V, b), {W, V, b}, true, eps2);
  //  CHECK_(Affine<GeluOp>(W, V, b), {W, V, b}, true, eps2);
  //}
}
//
//TEMPLATE_TEST_CASE("Affine w/ broadcast", "[affine]", Real, Half) {
//  using Scalar = TestType;
//  Real eps = std::is_same_v<Scalar, Half> ? 2e-3 : 1e-6; // TODO: 😢
//  Real eps2 = std::is_same_v<Scalar, Half> ? 2e-3 : 1e-4;
//  auto W = Values<2>({{1, 2, 3},
//                      {4, 5, 6}})->cast<Scalar>();
//  auto V = Values<2>({{ 6,  5},
//                      { 4, -1},
//                      {-2, -3}})->cast<Scalar>();
//  auto b = Values<2>({{0.1},
//                      {0.2}})->cast<Scalar>();
//
//  auto WVb = Values<2>({{ 8.1, -5.9},
//                        {32.2, -2.8}})->cast<Scalar>();
//
//  SECTION("Affine") {
//    check(Affine(W, V, b), WVb, eps);
//    CHECK_(Affine(W, V, b), {W, V, b}, true, eps2);
//  }
//}
//
//TEMPLATE_TEST_CASE("Affine w/ high rank", "[affine]", Real, Half) {
//  using Scalar = TestType;
//  Real eps = std::is_same_v<Scalar, Half> ? 2e-3 : 1e-6; // TODO: 😢
//  Real eps2 = std::is_same_v<Scalar, Half> ? 2e-3 : 1e-4;
//  auto W = Values<2>({{1, 2, 3}, // 2 x 3
//                      {4, 5, 6}})->cast<Scalar>();
//  auto V = Values<3>({{{ 6,  5},{ 6,  5}}, // 3 x 2 x 2
//                      {{ 4, -1},{ 4, -1}},
//                      {{-2, -3},{-2, -3}}})->cast<Scalar>();
//  auto b = Values<1>({0.1, // 2
//                      0.2})->cast<Scalar>();
//
//  auto WVb = Values<3>({{{ 8.1, -5.9},{ 8.1, -5.9}}, // 2 x 2 x 2
//                        {{32.2, -2.8},{32.2, -2.8}}})->cast<Scalar>();
//
//  SECTION("Affine") {
//    check(Affine(W, V, b), WVb, eps);
//    CHECK_(Affine(W, V, b), {W, V, b}, true, eps2);
//  }
//}
//
//TEMPLATE_TEST_CASE("InPlaceAdd", "[inplace][arithmetic]", Real, Half) {
//  using Scalar = TestType;
//  auto W = Random(Dev, {2, 3})->cast<Scalar>();
//  auto V = Random(Dev, {2, 3})->cast<Scalar>();
//  auto U = Random(Dev, {2, 3})->cast<Scalar>();
//
//  auto a1 = Add(W, V, U);
//  auto a2 = Add(W, V, V);
//  Graph(a1).forward();
//  Graph(a2).forward();
//
//  // Need one level of indirection because of how gradcheck perturbs values and
//  //   how in-place nodes reuse value tensors. Hence the multiply by 1. This
//  //   only applies to testing.
//  check(InPlaceAdd(W * 1, V, U), a1);
//  check(InPlaceAdd(W * 1, V, V), a2);
//  CHECK_(InPlaceAdd(W * 1, V, U), {W, V, U});
//  CHECK_(InPlaceAdd(W * 1, V, V), {W, V});
//}
//
//TEMPLATE_TEST_CASE("InPlaceAddScalar", "[inplace][arithmetic]", Real, Half) {
//  using Scalar = TestType;
//  auto W = Random(Dev, {2, 3})->cast<Scalar>();
//
//  auto a1 = W + 3.14;
//  auto a2 = W - 5;
//  Graph(a1).forward();
//  Graph(a2).forward();
//
//  check(InPlaceAddScalar(1 * W, 3.14), a1);
//  check(InPlaceAddScalar(1 * W, -5), a2);
//  CHECK_(InPlaceAddScalar(1 * W, 3.14), {W});
//  CHECK_(InPlaceAddScalar(1 * W, -5), {W});
//}
//
//TEMPLATE_TEST_CASE("InPlaceCwiseProd", "[inplace][arithmetic]", Real, Half) {
//  using Scalar = TestType;
//  auto W = Random(Dev, {2, 3, 2})->cast<Scalar>();
//  auto V = Random(Dev, {2, 3, 2})->cast<Scalar>();
//
//  auto p = CwiseProd(W, V);
//  Graph(p).forward();
//
//  check(InPlaceCwiseProd(1 * W, V), p);
//  CHECK_(InPlaceCwiseProd(1 * W, V), {W, V});
//}
//
//TEMPLATE_TEST_CASE("InPlaceProdScalar", "[inplace][arithmetic]", Real, Half) {
//  using Scalar = TestType;
//  auto W = Random(Dev, {2, 3})->cast<Scalar>();
//
//  auto p1 = W * 3.14;
//  auto p2 = W * -5;
//  Graph(p1).forward();
//  Graph(p2).forward();
//
//  check(InPlaceProdScalar(1 * W, 3.14), p1);
//  check(InPlaceProdScalar(1 * W, -5), p2);
//  CHECK_(InPlaceProdScalar(1 * W, 3.14), {W});
//  CHECK_(InPlaceProdScalar(1 * W, -5), {W});
//}
//
//TEMPLATE_TEST_CASE("InPlaceMask", "[inplace]", Real, Half) {
//  using Scalar = TestType;
//  auto W = Random(Dev, {2, 3, 2})->cast<Scalar>();
//  auto m1 = Random(Dev, {2, 3, 2})->cast<Scalar>();
//  auto m2 = Random(Dev, {2, 3, 1})->cast<Scalar>();
//  auto m3 = Random(Dev, {2, 1, 1})->cast<Scalar>();
//
//  auto set_mask = [](auto& m) {
//    m->set_random();
//    m->value() = (m->value().t() > Scalar(0)).template cast<Scalar>();
//    m->set_has_grad(false);
//  };
//
//  set_mask(m1);
//  set_mask(m2);
//  set_mask(m3);
//
//  CHECK_(InPlaceMask(W * 1, m1, 3.), {W, m1, m2, m3});
//  CHECK_(InPlaceMask(W * 1, m2, -3.), {W, m1, m2, m3});
//  CHECK_(InPlaceMask(W * 1, m3, 0.), {W, m1, m2, m3});
//}
//
//TEMPLATE_TEST_CASE("InPlaceSigmoid", "[inplace][nlnode]", Real, Half) {
//  using Scalar = TestType;
//  auto W = Random(Dev, {2, 3})->cast<Scalar>();
//
//  auto s = Sigmoid(W);
//  Graph(s).forward();
//
//  check(InPlaceSigmoid(1 * W), s);
//  CHECK_(InPlaceSigmoid(1 * W), {W});
//}

// clang-format on

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

#include <ginn/node/nlnode.h>
#include <ginn/node/pick.h>

#include "check_node.h"
#include "testutil.h"

using namespace ginn;

#ifdef GINN_ENABLE_GPU
constexpr bool gpu_enabled = true;
#else
constexpr bool gpu_enabled = false;
#endif

// clang-format off


TEMPLATE_TEST_CASE("Pickles", "[pick][nlnode]", Real, Half) {
  using Scalar = TestType;
  auto W = Values<2>({{-0.5,  0.55, -0.45},
                      { 1. ,  2.  , -1.  },
                      { 0. ,  0.  ,  0.  },
                      { 0.3, -0.33,  1.3 }})->cast<Scalar>();
  //auto sm = Values<2>({{0.106884, 0.159876,  0.112361},
  //                     {0.47902,  0.68157,   0.0648268},
  //                     {0.176222, 0.0922404, 0.176218},
  //                     {0.237874, 0.0663138, 0.646594}});
  auto p     = Values<2>({{0.3, 0.55, -1.}})->cast<Scalar>();
  auto psm   = Values<2>({{0.23787436, 0.15987601, 0.06482681}})->cast<Scalar>();
  auto pnlsm = Values<2>({{1.43601264, 1.8333567,  2.73603603}})->cast<Scalar>();

  auto iv = std::vector<Int>{3, 0, 1};
  auto it = Values<1>({3, 0, 1})->cast<Int>();
  it->set_has_grad(false);

  SECTION("Pick") {
    check(Pick(W, iv), p);
    check(Pick(W, it), p);
    if constexpr (not gpu_enabled and std::is_same_v<Scalar, Real>) {
      check_grad(Pick(W, iv), {W}, true);
      check_grad(Pick(W, it), {W}, true);
    }
    if constexpr (gpu_enabled and ginn::is_floating_point_v<Scalar>) {
      auto [W_, it_] = to_gpu(W, it);
      compare_devices(Pick(W, iv), {W}, Pick(W_, iv ), {W_});
      compare_devices(Pick(W, it), {W}, Pick(W_, it_), {W_});
    }
  }

  SECTION("PickSoftmax") {
    check(PickSoftmax(W, iv),   psm, std::is_same_v<Scalar, Half> ? 1e-3 : 1e-6);
    check(PickSoftmax(W, it),   psm, std::is_same_v<Scalar, Half> ? 1e-3 : 1e-6);
    check(Pick(Softmax(W), iv), psm, std::is_same_v<Scalar, Half> ? 1e-3 : 1e-6);
    check(Pick(Softmax(W), it), psm, std::is_same_v<Scalar, Half> ? 1e-3 : 1e-6);

    if constexpr (not gpu_enabled and std::is_same_v<Scalar, Real>) {
      check_grad(PickSoftmax(W, iv),   {W}, true);
      check_grad(PickSoftmax(W, it),   {W}, true);
      check_grad(Pick(Softmax(W), iv), {W}, true);
      check_grad(Pick(Softmax(W), it), {W}, true);
    }
    if constexpr (gpu_enabled and ginn::is_floating_point_v<Scalar>) {
      auto [W_, it_] = to_gpu(W, it);
      compare_devices(PickSoftmax(W, iv), {W}, PickSoftmax(W_, iv ), {W_});
      compare_devices(PickSoftmax(W, it), {W}, PickSoftmax(W_, it_), {W_});
      compare_devices(Pick(Softmax(W), iv), {W}, Pick(Softmax(W_), iv ), {W_});
      compare_devices(Pick(Softmax(W), it), {W}, Pick(Softmax(W_), it_), {W_});
    }
  }

  SECTION("PickNegLogSoftmax") {
    check(PickNegLogSoftmax(W, iv),   pnlsm, std::is_same_v<Scalar, Half> ? 1e-3 : 1e-6);
    check(PickNegLogSoftmax(W, it),   pnlsm, std::is_same_v<Scalar, Half> ? 1e-3 : 1e-6);
    check(-Log(PickSoftmax(W, iv)),   pnlsm, std::is_same_v<Scalar, Half> ? 1e-3 : 1e-6);
    check(-Log(PickSoftmax(W, it)),   pnlsm, std::is_same_v<Scalar, Half> ? 1e-3 : 1e-6);
    check(Pick(-Log(Softmax(W)), iv), pnlsm, std::is_same_v<Scalar, Half> ? 1e-3 : 1e-6);
    check(Pick(-Log(Softmax(W)), it), pnlsm, std::is_same_v<Scalar, Half> ? 1e-3 : 1e-6);

    if constexpr (not gpu_enabled and std::is_same_v<Scalar, Real>) {
      check_grad(PickNegLogSoftmax(W, iv),   {W},     true);
      check_grad(PickNegLogSoftmax(W, it),   {W, it}, true);
      check_grad(-Log(PickSoftmax(W, iv)),   {W},     true);
      check_grad(-Log(PickSoftmax(W, it)),   {W, it}, true);
      check_grad(Pick(-Log(Softmax(W)), iv), {W},     true);
      check_grad(Pick(-Log(Softmax(W)), it), {W, it}, true);
    }
    if constexpr (gpu_enabled and ginn::is_floating_point_v<Scalar>) {
      auto [W_, it_] = to_gpu(W, it);
      constexpr auto eps = std::is_same_v<Scalar, Half> ? 1e-3 : 1e-4;
      compare_devices(PickNegLogSoftmax(W, iv),   {W}, PickNegLogSoftmax(W_, iv),    {W_}, eps);
      compare_devices(PickNegLogSoftmax(W, it),   {W}, PickNegLogSoftmax(W_, it_),   {W_}, eps);
      compare_devices(-Log(PickSoftmax(W, iv)),   {W}, -Log(PickSoftmax(W_, iv)),    {W_}, eps);
      compare_devices(-Log(PickSoftmax(W, it)),   {W}, -Log(PickSoftmax(W_, it_)),   {W_}, eps);
      compare_devices(Pick(-Log(Softmax(W)), iv), {W}, Pick(-Log(Softmax(W_)), iv),  {W_}, eps);
      compare_devices(Pick(-Log(Softmax(W)), it), {W}, Pick(-Log(Softmax(W_)), it_), {W_}, eps);
    }
  }
}

TEMPLATE_TEST_CASE("PickNegLogSigmoid", "[pick][nlnode]", Real, Half) {
  using Scalar = TestType;
  auto W = Values<2>({{-0.5,  0.55, -0.45},
                      { 1. ,  2.  , -1.  },
                      { 0. ,  0.  ,  0.  },
                      { 0.3, -0.33,  1.3 }})->cast<Scalar>();
  auto p = Values<2>({{0, 1, 0},
                      {1, 0, 1},
                      {0, 1, 0},
                      {1, 0, 1}})->cast<Int>();
  p->set_has_grad(false);
  auto pnls = Values<2>({{0.47407698, 0.45549248, 0.49324895},
                         {0.31326169, 2.12692801, 1.31326169},
                         {0.69314718, 0.69314718, 0.69314718},
                         {0.55435524, 0.54169836, 0.24100845}})->cast<Scalar>();

  check(PickNegLogSigmoid(W, p), pnls, std::is_same_v<Scalar, Half> ? 2e-3 : 1e-6);
  if constexpr (not gpu_enabled and std::is_same_v<Scalar, Real>) {
    check_grad(PickNegLogSigmoid(W, p), {W}, true);
  }
  if constexpr (gpu_enabled and ginn::is_floating_point_v<Scalar>) {
    auto [W_, p_] = to_gpu(W, p);
    compare_devices(PickNegLogSigmoid(W,  p ), {W },
                    PickNegLogSigmoid(W_, p_), {W_});
  }
}
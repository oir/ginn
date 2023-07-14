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

#ifndef GINN_INIT_H
#define GINN_INIT_H

#include <ginn/node/weight.h>

namespace ginn {

template <typename Scalar, DeviceKind Kind>
class Initer {
 public:
  virtual void init(Tensor<Scalar, Kind>& w) = 0;
  void init(const WeightPtr<Scalar, Kind>& w) { init(w->value()); }
  void init(const std::vector<WeightPtr<Scalar, Kind>>& ws) {
    for (auto w : ws) { init(w); }
  }

  virtual ~Initer() = default;
};

namespace init {

// Initers assume node::Weight value matrix has the right size already

template <typename Scalar, DeviceKind Kind>
class Xavier : public Initer<Scalar, Kind> {
 public:
  using Initer<Scalar, Kind>::init;

  Xavier() = default;

  void init(Tensor<Scalar, Kind>& w) override {
    Size rows = w.shape2()[0];
    Size cols = w.shape2()[1];
    Real a = sqrt(6. / (0.5 * (rows + cols)));
    w.set_random();
    w = w.t() * Raw<Scalar>(a);
  }
};

template <typename Scalar, DeviceKind Kind>
class Uniform : public Initer<Scalar, Kind> {
 public:
  Scalar range;

  using Initer<Scalar, Kind>::init;

  template <typename RhsScalar = Raw<Scalar>>
  Uniform(RhsScalar range = RhsScalar(1.)) : range(range) {}

  void init(Tensor<Scalar, Kind>& w) override {
    w.set_random();
    w = w.t() * range;
  }
};

template <typename Scalar, DeviceKind Kind>
class Zero : public Initer<Scalar, Kind> {
 public:
  void init(Tensor<Scalar, Kind>& w) override { w.fill(Raw<Scalar>(0)); }
};

} // end namespace init
} // end namespace ginn

#endif

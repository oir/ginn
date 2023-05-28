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

#ifndef GINN_DEF_H
#define GINN_DEF_H

#ifdef GINN_ENABLE_GPU // cuda
#define EIGEN_USE_GPU
#include <cublas_v2.h>
#include <cuda.h>
#include <cuda_runtime_api.h>
#include <curand.h>
#endif

#include <ginn/except.h> // this undefines some Eigen errors, needs to be included before Eigen
#include <unsupported/Eigen/CXX11/Tensor> // Eigen

#include <ginn/scalar.h>

namespace ginn {

using Size = long;

template <typename Scalar>
using Matrix = Eigen::Matrix<Raw<Scalar>, -1, -1>;

template <typename Scalar>
using Vector = Eigen::Vector<Raw<Scalar>, -1>;

template <typename Scalar>
using RowVector = Eigen::RowVector<Raw<Scalar>, -1>;

template <typename Scalar>
using MatrixMap = Eigen::Map<Matrix<Scalar>>;

template <typename Scalar>
using VectorMap = Eigen::Map<Vector<Scalar>>;

template <typename Scalar, int N>
using TensorMap = Eigen::TensorMap<Eigen::Tensor<Raw<Scalar>, N>>;

namespace literals {

inline Real operator"" _r(long double x) { return x; }
inline Real operator"" _r(unsigned long long x) { return x; }

inline Eigen::half operator"" _h(long double x) { return Eigen::half{x}; }
inline Eigen::half operator"" _h(unsigned long long x) { return Eigen::half{x}; }

} // namespace literals

} // namespace ginn

#ifdef GINN_ENABLE_GPU
#include "cudef.h"
#endif

#endif

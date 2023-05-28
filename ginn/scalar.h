#ifndef GINN_SCALAR_H
#define GINN_SCALAR_H

namespace ginn {

#ifdef GINN_DOUBLE_PRECISION
using Real = double;
#else
using Real = float;
#endif
//using Half = Eigen::half;

using Int = int;

struct Half {};

// Point of "Raw" type of a "Scalar" is to hide "Eigen::" from Ginn signatures.
// e.g. Raw<ginn::Half>::type will point to Eigen::half, and we will use ginn::Half
// in Tensor or Node template parameters instead of Eigen::half.

template <typename T>
struct RawImpl {
  using type = T;
};

template <>
struct RawImpl<Half> {
  using type = Eigen::half;
};


template <typename T>
using Raw = typename RawImpl<T>::type;


} // namespace ginn

#endif

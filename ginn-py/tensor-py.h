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

#ifndef GINN_PY_TENSOR_PY_H
#define GINN_PY_TENSOR_PY_H

#include <ginn/def.h>

#include <pybind11/eigen.h>
#include <pybind11/operators.h>
#include <pybind11/pybind11.h>

#include <ginn/tensor.h>
#include <ginn/util/tensorio.h>

#include <ginn-py/util-py.h>

namespace ginn {
namespace python {

namespace py = pybind11;

// This is a helper type enum to dispatch things based on the scalar type
// on the Python side.
enum class Scalar_ { Real, Half, Int, Bool };

template <typename Scalar>
Scalar_ scalar_() {
  if constexpr (std::is_same_v<Scalar, Real>) {
    return Scalar_::Real;
  } else if constexpr (std::is_same_v<Scalar, Half>) {
    return Scalar_::Half;
  } else if constexpr (std::is_same_v<Scalar, Int>) {
    return Scalar_::Int;
  } else if constexpr (std::is_same_v<Scalar, bool>) {
    return Scalar_::Bool;
  } else {
    GINN_THROW("Unexpected scalar type!");
    return {};
  }
}
template <typename Scalar, enum DeviceKind Kind>
auto declare_tensor_of(py::module_& m) {
  return py::class_<Tensor<Scalar, Kind>>(m, name<Scalar, Kind>("Tensor"));
}

template <typename Scalar, enum DeviceKind Kind, typename PyClass>
void bind_tensor_of(PyClass& m) {
  using namespace pybind11::literals;
  using T = Tensor<Scalar, Kind>;

  m.def(py::init<>());
  m.def(py::init<DevPtr<Kind>>(), "device"_a);
  m.def(py::init<Shape>(), "shape"_a);
  // m.def(py::init<Shape, const std::vector<Scalar>&>(), "shape"_a, "val"_a);
  m.def(py::init<DevPtr<Kind>, Shape>(), "device"_a, "shape"_a);
  m.def(py::init<DevPtr<Kind>, Shape, std::vector<Scalar>>(),
        "device"_a,
        "shape"_a,
        "val"_a);
  m.def_property_readonly("dev", &T::dev);
  m.def_property("shape", &T::shape, &T::resize);
  m.def_property_readonly("size", py::overload_cast<>(&T::size, py::const_));
  if constexpr (std::is_same_v<Scalar, Half>) {
    m.def("list", [](const T& t) { return t.template cast<Real>().vector(); });
  } else {
    m.def("list", &T::vector);
  }
  m.def("v", py::overload_cast<>(&T::v));
  m.def("m", py::overload_cast<>(&T::m));
  m.def("item", &T::item);
  m.def("real", &T::template cast<Real>);
  m.def("half", &T::template cast<Half>);
  m.def("int", &T::template cast<Int>);
  m.def("bool", &T::template cast<bool>);
  m.def("cast", [](const T& t, Scalar_ scalar) -> py::object {
    switch (scalar) {
    case Scalar_::Real: return py::cast(t.template cast<Real>());
    case Scalar_::Half: return py::cast(t.template cast<Half>());
    case Scalar_::Int: return py::cast(t.template cast<Int>());
    case Scalar_::Bool: return py::cast(t.template cast<bool>());
    default: return {};
    }
  });
  m.def("set_zero", &T::set_zero);
  m.def("set_ones", &T::set_ones);
  m.def("set_random", &T::set_random);

  if constexpr (std::is_same_v<Scalar, bool>) {
    for_range<5>([&](auto arr) { m.def("set", &T::template set<arr.size()>); });
  } else {
    for_range<5>(
        [&](auto arr) { m.def("set", &T::template set<arr.size(), Real>); });
    for_range<5>(
        [&](auto arr) { m.def("set", &T::template set<arr.size(), Int>); });
  }

  // do I now need to instantiate this for all device types?
  m.def(
      "copy_to", &T::template copy_to<std::shared_ptr<CpuDevice>>, "device"_a);
#ifdef GINN_ENABLE_GPU
  m.def(
      "copy_to", &T::template copy_to<std::shared_ptr<GpuDevice>>, "device"_a);
  // m.def("copy_to", &Tensor<Scalar, CPU>::template
  // copy_to<std::shared_ptr<GpuDevice>>, "device"_a);
#endif
  // m.def("move_to", &T::move_to, "device"_a);
  m.def("maybe_copy_to",
        &T::template maybe_copy_to<std::shared_ptr<CpuDevice>>,
        "device"_a);
  m.def_property_readonly("scalar", [](const T&) { return scalar_<Scalar>(); });
  m.def("__repr__", [&](const T& t) {
    std::stringstream ss;
    ss << t;
    return ss.str();
  });
  m.def(
      "__eq__",
      [](const T& a, const T& b) { return a == b; },
      py::is_operator());
}

py::class_<Tensor<Real, CPU>> bind_tensor(py::module_& m);
void bind_tensor_gpu(py::module_& m, py::class_<Tensor<Real, CPU>>&);

} // namespace python
} // namespace ginn

#endif

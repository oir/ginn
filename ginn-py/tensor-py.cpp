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

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <ginn-py/tensor-py.h>

#include <ginn-py/util-py.h>

namespace ginn {
namespace python {

GINN_PY_MAKE_SCALAR_DISPATCHER(Tensor, CPU);

py::class_<Tensor<Real, CPU>> bind_tensor(py::module_& m) {
  using namespace py::literals;

  py::enum_<Scalar_>(m, "Scalar")
      .value("Real", Scalar_::Real)
      .value("Half", Scalar_::Half)
      .value("Int", Scalar_::Int)
      .value("Bool", Scalar_::Bool)
      .export_values();

  // making pybind know all tensor types first, so method docs contain the
  // appropriate python types throughout.
  auto mr = declare_tensor_of<Real, CPU>(m);
  auto mi = declare_tensor_of<Int, CPU>(m);
  auto mh = declare_tensor_of<Half, CPU>(m);
  auto mb = declare_tensor_of<bool, CPU>(m);

  bind_tensor_of<Real, CPU>(mr);
  bind_tensor_of<Int, CPU>(mi);
  bind_tensor_of<Half, CPU>(mh);
  bind_tensor_of<bool, CPU>(mb);

  // Why is &Tensor_<> an unknown type? -- might be a nvcc11.1 thing.
  m.def("Tensor",
        static_cast<py::object (*)(Scalar_)>(&Tensor_<>),
        "scalar"_a = Scalar_::Real);
  m.def("Tensor",
        &Tensor_<const DevPtr<CPU>&>,
        "device"_a,
        "scalar"_a = Scalar_::Real);
  m.def("Tensor",
        &Tensor_<const DevPtr<CPU>&, const Shape&>,
        "device"_a,
        "shape"_a,
        "scalar"_a = Scalar_::Real);
  m.def(
      "Tensor", &Tensor_<const Shape&>, "shape"_a, "scalar"_a = Scalar_::Real);

  return mr;
}

} // namespace python
} // namespace ginn

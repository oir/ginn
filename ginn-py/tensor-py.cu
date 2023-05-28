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

GINN_PY_MAKE_SCALAR_DISPATCHER(Tensor, GPU);

void bind_tensor_gpu(py::module_& m, TensorClasses& tc) {
  using namespace py::literals;

  // making pybind know all tensor types first, so method docs contain the
  // appropriate python types throughout.
  auto mr = declare_tensor_of<Real, GPU>(m);
  auto mi = declare_tensor_of<Int, GPU>(m);
  auto mh = declare_tensor_of<Half, GPU>(m);
  auto mb = declare_tensor_of<bool, GPU>(m);

  bind_tensor_of<Real, GPU>(mr);
  bind_tensor_of<Int, GPU>(mi);
  bind_tensor_of<Half, GPU>(mh);
  bind_tensor_of<bool, GPU>(mb);

  auto add_cross_device_copy = [](auto& t, auto scalar) {
    using Scalar = decltype(scalar);
    t.def("copy_to",
          &Tensor<Scalar, CPU>::template copy_to<std::shared_ptr<GpuDevice>>,
          "device"_a);
  };

  auto& [rt, ht, it, bt] = tc;
  add_cross_device_copy(rt, Real());
  add_cross_device_copy(ht, Half());
  add_cross_device_copy(it, Int());
  add_cross_device_copy(bt, bool());

  // Why is &Tensor_<> an unknown type? -- might be a nvcc11.1 thing.
  // m.def("Tensor",
  //      static_cast<py::object (*)(Scalar_)>(&Tensor_<>),
  //      "scalar"_a = Scalar_::Real);
  m.def("Tensor",
        &Tensor_<const DevPtr<GPU>&>,
        "device"_a,
        "scalar"_a = Scalar_::Real);
  m.def("Tensor",
        &Tensor_<const DevPtr<GPU>&, const Shape&>,
        "device"_a,
        "shape"_a,
        "scalar"_a = Scalar_::Real);
  m.def(
      "Tensor", &Tensor_<const Shape&>, "shape"_a, "scalar"_a = Scalar_::Real);
}

} // namespace python
} // namespace ginn

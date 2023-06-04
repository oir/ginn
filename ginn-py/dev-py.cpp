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

// #include <pybind11/operators.h>
//  NOTE: Using py::self way of operator binding yields template type deduction
//  errors in the particular nvcc I'm using.
#include <pybind11/pybind11.h>

#include <ginn/dev.h>

#include <ginn-py/dev-py.h>

namespace ginn {
namespace python {

namespace py = pybind11;

void bind_dev(py::module_& m) {
  using namespace py::literals;

  py::enum_<DeviceKind>(m, "DeviceType")
      .value("CPU", CPU)
      .value("GPU", GPU)
      .value("NULL_DEV", NULL_DEV);

  py::class_<DeviceId>(m, "DeviceId")
      .def("__repr__",
           [](const DeviceId& i) -> std::string {
             return std::string("<DeviceId with kind: ") +
                    (i.kind == 0 ? "CPU" : (i.kind == 1) ? "GPU" : "NULL_DEV") +
                    ", idx: " + std::to_string(i.idx) + ">";
           })
      .def(
          "__eq__",
          [](const DeviceId& a, const DeviceId& b) { return a == b; },
          py::is_operator());

  py::class_<Device<CPU>, std::shared_ptr<Device<CPU>>>(m, "BaseCpuDevice")
      .def_property_readonly("kind", &Device<CPU>::kind)
      .def_property_readonly("id", &Device<CPU>::id)
      .def_property_readonly("precedence", &Device<CPU>::precedence);

  py::class_<CpuDevice, Device<CPU>, std::shared_ptr<CpuDevice>>(m,
                                                                 "CpuDevice");

  m.def("Cpu", &Cpu, "");
  m.def("cpu", &cpu, "");

  py::class_<PreallocCpuDevice,
             Device<CPU>,
             std::shared_ptr<PreallocCpuDevice>>(m, "PreallocCpuDevice")
      .def("clear", &PreallocCpuDevice::clear)
      .def_property_readonly("size", &PreallocCpuDevice::size)
      .def_property_readonly("used", &PreallocCpuDevice::used);

  m.def("PreallocCpu", &PreallocCpu, "");
  // m.def("gpus", &gpus);
}

} // namespace python
} // namespace ginn

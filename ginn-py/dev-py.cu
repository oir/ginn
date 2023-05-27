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

#include <ginn/dev.h>

#include <ginn-py/dev-py.h>

namespace ginn {
namespace python {

namespace py = pybind11;

inline int gpus_() {
  int num_gpus = -1;
  try {
    GINN_CUDA_CALL(cudaGetDeviceCount(&num_gpus));
  } catch (const CudaError&) { return 0; }
  return num_gpus;
}

void barrier() {
  // This is needed for proper timing since cuda calls are async and cpu code
  // continues execution immediately.
  for (int i = 0; i < gpus_(); i++) {
    GINN_CUDA_CALL(cudaSetDevice(i));
    GINN_CUDA_CALL(cudaDeviceSynchronize());
  }
}

void bind_dev_gpu(py::module_& m) {
  using namespace py::literals;

  py::class_<Device<GPU>, std::shared_ptr<Device<GPU>>>(m, "BaseGpuDevice")
      .def_property_readonly("kind", &Device<GPU>::kind)
      .def_property_readonly("id", &Device<GPU>::id)
      .def_property_readonly("precedence", &Device<GPU>::precedence);

  py::class_<GpuDevice, Device<GPU>, std::shared_ptr<GpuDevice>>(m,
                                                                 "GpuDevice");

  m.def("Gpu", &Gpu, py::arg("gpu_idx") = 0);
  m.def("gpu", &gpu, py::arg("gpu_idx") = 0);

  py::class_<PreallocGpuDevice,
             Device<GPU>,
             std::shared_ptr<PreallocGpuDevice>>(m, "PreallocGpuDevice")
      .def("clear", &PreallocGpuDevice::clear)
      .def_property_readonly("size", &PreallocGpuDevice::size)
      .def_property_readonly("used", &PreallocGpuDevice::used);

  m.def("PreallocGpu",
        py::overload_cast<size_t, size_t>(&PreallocGpu),
        "idx"_a,
        "size"_a);

  m.def("gpus", &gpus_);
  m.def("barrier", &barrier);
}

} // namespace python
} // namespace ginn

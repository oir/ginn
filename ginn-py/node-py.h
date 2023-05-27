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

#ifndef GINN_PY_NODE_PY_H
#define GINN_PY_NODE_PY_H

#include <pybind11/pybind11.h>

#include <ginn/node.h>

#include <ginn-py/tensor-py.h>
#include <ginn-py/util-py.h>

PYBIND11_DECLARE_HOLDER_TYPE(T, ginn::Ptr<T>)

namespace ginn {
namespace python {

namespace py = pybind11;

template <typename Scalar, enum DeviceKind Kind>
auto declare_node_of(py::module_& m) {
  using namespace pybind11::literals;

  auto node = py::class_<Node<Scalar, Kind>, BaseNode, Ptr<Node<Scalar, Kind>>>(
                  m, name<Scalar, Kind>("Node"))
                  .def("forward", &BaseNode::forward)
                  .def("reset_forwarded", &BaseNode::reset_forwarded)
                  .def("reset_grad", &BaseNode::reset_grad)
                  .def_property(
                      "forwarded",
                      [](const BaseNode& n) { return n.forwarded; },
                      [](BaseNode& n, bool val) { n.forwarded = val; });
  py::class_<BaseDataNode<Scalar, Kind>,
             Node<Scalar, Kind>,
             Ptr<BaseDataNode<Scalar, Kind>>>(
      m, name<Scalar, Kind>("BaseDataNode"))
      .def_property(
          "has_grad",
          py::overload_cast<>(&BaseDataNode<Scalar, Kind>::has_grad,
                              py::const_),
          py::overload_cast<bool>(&BaseDataNode<Scalar, Kind>::set_has_grad));
  auto data = py::class_<DataNode<Scalar, Kind>,
                         BaseDataNode<Scalar, Kind>,
                         Ptr<DataNode<Scalar, Kind>>>(
      m, name<Scalar, Kind>("DataNode"));

  return std::make_tuple(node, data);
}

template <typename Scalar, enum DeviceKind Kind, typename PyClass>
void bind_node_of(PyClass& m) {
  using namespace pybind11::literals;
  using T = Node<Scalar, Kind>;

  m.def_property_readonly("dev", &T::dev)
      .def_property_readonly("size", py::overload_cast<>(&T::size, py::const_))
      .def_property_readonly("shape",
                             py::overload_cast<>(&T::shape, py::const_))
      // TODO: Setters for value & grad
      .def_property_readonly("value", py::overload_cast<>(&T::value))
      .def_property_readonly("grad", py::overload_cast<>(&T::grad))
      .def_property_readonly("name", &T::name);
  m.def_property_readonly("scalar", [](const T&) { return scalar_<Scalar>(); });
}

template <typename Scalar, enum DeviceKind Kind, typename PyClass>
void bind_data_of(PyClass& m) {
  using namespace pybind11::literals;
  using T = DataNode<Scalar, Kind>;

  m // .def("move_to", &T::move_to, "device"_a)
      .def("fill", &T::fill, "val"_a)
      .def("set_zero", &T::set_zero)
      .def("set_ones", &T::set_ones)
      .def("set_random", &T::set_random);
  m.def("cast", [](const T& t, Scalar_ scalar) -> py::object {
    switch (scalar) {
    case Scalar_::Real: return py::cast(t.template cast<Real>());
    case Scalar_::Half: return py::cast(t.template cast<Half>());
    case Scalar_::Int: return py::cast(t.template cast<Int>());
    case Scalar_::Bool: return py::cast(t.template cast<bool>());
    default: return {};
    }
  });
  m.def("real", &T::template cast<Real>);
  m.def("half", &T::template cast<Half>);
  m.def("int", &T::template cast<Int>);
  m.def("bool", &T::template cast<bool>);
}

GINN_PY_MAKE_SCALAR_DISPATCHER_2(Data)
GINN_PY_MAKE_FLOATING_SCALAR_DISPATCHER(Random) // TODO: Int & bool

void bind_node(py::module_& m);
void bind_node_gpu(py::module_& m);

} // namespace python
} // namespace ginn

#endif
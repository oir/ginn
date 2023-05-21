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

#include <string>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <ginn/node.h>
#include <ginn/node/common.h>
//#include <ginn/node/compare.h> // need for operator<(), etc
//#include <ginn/node/data.h>
//#include <ginn/node/prod.h> // need for operator*()

//#include <ginn-py/node/affine-py.h>
#include <ginn-py/node/common-py.h>
//#include <ginn-py/node/compare-py.h>
//#include <ginn-py/node/layout-py.h>
//#include <ginn-py/node/nonlin-py.h>
//#include <ginn-py/node/pick-py.h>
//#include <ginn-py/node/prod-py.h>
//#include <ginn-py/node/reduce-py.h>
//#include <ginn-py/node/select-py.h>
//#include <ginn-py/node/weight-py.h>

#include <ginn-py/tensor-py.h>
#include <ginn-py/util-py.h>

#include <ginn-py/node-py.h>

namespace ginn {
namespace python {

namespace py = pybind11;

void bind_node_gpu(py::module_& m) {
  using namespace pybind11::literals;

  py::class_<BaseNode, Ptr<BaseNode>>(m, "BaseNode");
  py::class_<Graph>(m, "Graph")
      .def(py::init<Ptr<BaseNode>>())
      .def("forward", &Graph::forward)
      .def("reset_forwarded", &Graph::reset_forwarded)
      .def("reset_grad", &Graph::reset_grad)
      .def("backward", &Graph::backward, "loss_coeff"_a);

  // making pybind know all node types first, so method docs contain the
  // appropriate python types throughout.
  auto [rnode, rdata] = declare_node_of<Real, CPU>(m);
  auto [inode, idata] = declare_node_of<Int, CPU>(m);
  // auto [hnode, hdata] = declare_node_of<Half, CPU>(m);
  auto [bnode, bdata] = declare_node_of<bool, CPU>(m);

  bind_node_of<Real, CPU>(rnode);
  bind_node_of<Int, CPU>(inode);
  // bind_node_of<Half, CPU>(hnode);
  bind_node_of<bool, CPU>(bnode);

  bind_data_of<Real, CPU>(rdata);
  bind_data_of<Int, CPU>(idata);
  // bind_data_of<Half, CPU>(hdata);
  bind_data_of<bool, CPU>(bdata);

  for_each<Real, /*Half,*/ Int, bool>([&](auto scalar) {
    using Scalar = decltype(scalar);
    // nvcc 11.1 forces me to use an explicit static cast here.
    m.def(name<Scalar, CPU>("Data"),
          &Data<Scalar, const DevPtr<CPU>&, const Shape&>,
          "dev"_a,
          "shape"_a);
  });

  m.def("Data",
        &Data_<const DevPtr<CPU>&>,
        "device"_a,
        "scalar"_a = Scalar_::Real);
  m.def("Data",
        &Data_<const DevPtr<CPU>&, const Shape&>,
        "device"_a,
        "shape"_a,
        "scalar"_a = Scalar_::Real);
  m.def(
      "Data",
      //&Data_<const Shape&>,
      [](const Shape& shape, Scalar_ scalar) {
        return Data_<const DevPtr<CPU>&, const Shape&>(cpu(), shape, scalar);
      },
      "shape"_a,
      "scalar"_a = Scalar_::Real);
  m.def("Data", [&](const Matrix<Real>& m) {
    auto x = Data<Real>(cpu(), {m.rows(), m.cols()});
    x->value().m() = m;
    return x;
  });

  m.def("Random",
        &Random_<const DevPtr<CPU>&, const Shape&>,
        "device"_a,
        "shape"_a,
        "scalar"_a = Scalar_::Real);
  m.def(
      "Random",
      //&Random_<const Shape&>,
      [](const Shape& shape, Scalar_ scalar) {
        return Random_<const DevPtr<CPU>&, const Shape&>(cpu(), shape, scalar);
      },
      "shape"_a,
      "scalar"_a = Scalar_::Real);

  for_range<5>([&](auto arr) {
    constexpr size_t N = arr.size();
    m.def("Values",
          py::overload_cast<NestedInitList<N, Real>>(&Values<N, Real>),
          "values"_a);
    m.def("Values",
          py::overload_cast<DevPtr<CPU>, NestedInitList<N, Real>>(
              &Values<N, Real, DevPtr<CPU>>),
          "dev"_a,
          "values"_a);
  });

  // bind_affine_nodes(m);
  bind_common_nodes(m);
  // bind_compare_nodes(m);
  // bind_layout_nodes(m);
  // bind_nonlin_nodes(m);
  // bind_pick_nodes(m);
  // bind_prod_nodes(m);
  // bind_reduce_nodes(m);
  // bind_select_nodes(m);

  // bind_weight_node(m);

  // add operator overloads to base node because we cannot do free functions
  // op_overload_helper(Real(), rnode);
  // op_overload_helper(Half(), hnode);
  // op_overload_helper(Int(), inode);
}

} // namespace python
} // namespace ginn

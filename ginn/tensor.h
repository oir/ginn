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

#ifndef GINN_TENSOR_H
#define GINN_TENSOR_H

#include <ginn/def.h>
#include <ginn/dev.h>
#include <ginn/eigenop/helpers.h>
#include <ginn/except.h>
#include <ginn/util/util.h>
#include <utility>
#include <vector>

namespace ginn {

// Tensor class seems to be a necessary evil because Eigen does not
// manage its own memory when GPU devices are used.

using Shape = std::vector<Size>;
template <Size N>
using Index = Eigen::array<Size, N>;

template <Size N>
Shape IndexToShape(const Index<N>& index) {
  Shape shape(N);
  for (Size i = 0; i < N; i++) { shape[i] = index[i]; }
  return shape;
}

template <Size N>
Index<N> ShapeToIndex(const Shape& shape) {
  GINN_ASSERT(N == shape.size());
  Index<N> rval;
  for (Size i = 0; i < N; i++) { rval[i] = shape[i]; }
  return rval;
}

// Forward declare helper types. These are invoked when a Tensor is on the
// lefthand side of a statement.

template <typename, DeviceKind>
class LhsExpr;

template <typename, Size, DeviceKind>
class SliceExpr;

template <typename, Size, DeviceKind>
class ChipExpr;

// Core Tensor class, specialized as Tensor and IntTensor on ScalarType Real and
// Int, respectively.
template <typename ScalarType = Real, DeviceKind Kind = CPU>
class Tensor {
 public:
  using Scalar = ScalarType;
  using RawScalar = Raw<Scalar>;
  static constexpr auto device_kind = Kind;

 private:
  DevPtr<Kind> dev_ = nullptr;
  Shape shape_ = {0};
  RawScalar* data_ = nullptr; // owned in most cases
  bool owns_mem_ = true;      // whether this Tensor owns data_

 public:
  DevPtr<Kind> dev() const { return dev_; }
  Shape shape() const { return shape_; }
  RawScalar* data() { return data_; }

  static Size size(const Shape& shape) {
    Size i = 1;
    for (auto j : shape) { i *= j; }
    return i;
  }

  Size size() const { return size(shape()); }

  // Move this tensor to another device
  // auto& move_to(const DevPtr& to) {
  //  GINN_ASSERT(owns_mem_);
  //  if (dev_ == to) { return *this; }
  //  Tensor<Scalar> from(dev_);
  //  from.data_ = data_;
  //  from.shape_ = shape_; // to make sure destructor deallocates this

  //  dev_ = to;
  //  data_ = nullptr;

  //  if (size() > 0) {
  //    allocate(size());
  //    copy(from.dev(), from.data_, size());
  //  }

  //  return *this;
  //}

  // Copy this tensor to another device
  template <typename OtherDevPtr>
  auto copy_to(const OtherDevPtr& to) const {
    const static auto OtherKind = OtherDevPtr::element_type::device_kind;
    return Tensor<Scalar, OtherKind>(to, *this);
  }

  // If tensor not on specified _physical_ device, copy to it. Otherwise return
  // a shallow copy based on Tensor::map() which uses the same storage
  template <typename OtherDevPtr>
  auto maybe_copy_to(const OtherDevPtr& to) {
    const static auto OtherKind = OtherDevPtr::element_type::device_kind;
    if constexpr (Kind == OtherKind) {
      if (dev_->id() == to->id()) {
        Tensor<Scalar, OtherKind> rval;
        rval.map(*this);
        return rval;
      } else {
        return copy_to(to);
      }
    } else {
      return copy_to(to);
    }
  }

  RawScalar item() const {
    GINN_ASSERT(size() == 1, "item() can be invoked on size 1 tensors!");
    return copy_to(cpu()).v()[0];
  }

 private:
  // Manage memory
  void allocate(Size size) {
    GINN_ASSERT(data_ == nullptr);
    GINN_ASSERT(owns_mem_, "Attempted to allocate when not owning memory!");
    if (size > 0) { data_ = (RawScalar*)dev_->alloc(size * sizeof(RawScalar)); }
  }

  template <DeviceKind OtherKind>
  void copy(const DevPtr<OtherKind>& from, RawScalar* other_data, Size size) {
    dev_->copy(*from, data_, other_data, size * sizeof(RawScalar));
  }

  void reallocate(Size size) {
    GINN_ASSERT(owns_mem_, "Attempted to reallocate when not owning memory!");
    if (size > 0) {
      data_ = (RawScalar*)dev_->realloc((void*)data_, size * sizeof(RawScalar));
    } else {
      free();
    }
  }

  void free() {
    GINN_ASSERT(owns_mem_, "Attempted to free when not owning memory!");
    if (size() > 0) { dev_->free(data_); }
    data_ = nullptr;
  }

 public:
  // Construct
  Tensor(DevPtr<Kind> dev = default_dev<Kind>()) : dev_(std::move(dev)) {}
  Tensor(DevPtr<Kind> dev, Shape shape)
      : dev_(std::move(dev)), shape_(std::move(shape)) {
    allocate(size());
  }
  Tensor(DevPtr<Kind> dev, Shape shape, RawScalar val)
      : Tensor<Scalar, Kind>(std::move(dev), std::move(shape)) {
    fill(val);
  }
  // can I make these ctor available only to DeviceKind==CPU?
  Tensor(Shape shape)
      : Tensor<Scalar, Kind>(default_dev<Kind>(), std::move(shape)) {}
  // Tensor(Shape shape, const std::vector<Scalar>& val)
  //     : Tensor<Scalar>(std::move(shape)) {
  //   GINN_ASSERT(size() == (Size)val.size(),
  //               "Size of Shape (" + std::to_string(size()) +
  //                   ") does not match size of values (" +
  //                   std::to_string(val.size()) + ")!");
  //   auto vmap = v();
  //   for (size_t i = 0; i < val.size(); i++) { vmap[i] = val[i]; }
  // }
  Tensor(DevPtr<Kind> dev, Shape shape, std::vector<RawScalar> val)
      : Tensor<Scalar, Kind>(dev, shape) {
    if constexpr (Kind == CPU) {
      GINN_ASSERT(size() == (Size)val.size(),
                  "Size of Shape (" + std::to_string(size()) +
                      ") does not match size of values (" +
                      std::to_string(val.size()) + ")!");
      auto vmap = v();
      for (size_t i = 0; i < val.size(); i++) { vmap[i] = val[i]; }
    } else {
      Tensor<Scalar, CPU> tmp(cpu(), shape, val);
      *this = tmp;
    }
  }

  template <int Rank>
  Tensor(DevPtr<Kind> dev, NestedInitList<Rank, RawScalar> val)
      : dev_(std::move(dev)), shape_(shape_of<Size, Rank, RawScalar>(val)) {
    set<Rank>(val);
  }

  // Ditto for CPU
  template <int Rank>
  Tensor(NestedInitList<Rank, RawScalar> val)
      : dev_(cpu()), shape_(shape_of<Size, Rank, RawScalar>(val)) {
    set<Rank>(val);
  }

  // Copy & Move construct
  Tensor(const Tensor<Scalar, Kind>& other)
      : dev_(other.dev_), shape_(other.shape_) {
    allocate(size());
    copy(other.dev_, other.data_, size());
  }
  Tensor(Tensor<Scalar, Kind>&& other)
      : dev_(other.dev_),
        shape_(other.shape_),
        data_(other.data_),
        owns_mem_(other.owns_mem_) {
    other.data_ = nullptr;
    other.shape_ = {0};
  }

  // Copy & Move assign
  template <DeviceKind OtherKind>
  auto& operator=(const Tensor<Scalar, OtherKind>& other) {
    if constexpr (Kind == OtherKind) {
      if (this == &other) { return *this; }
    }
    resize(other.shape_);
    copy(other.dev_, other.data_, size());
    return *this;
  }

  auto& operator=(const Tensor<Scalar, Kind>& other) {
    if (this == &other) { return *this; }
    resize(other.shape_);
    copy(other.dev_, other.data_, size());
    return *this;
  }

  auto& operator=(Tensor<Scalar, Kind>&& other) {
    // TODO: is it safe to move across different Devices if they lie on the same
    // physical device?
    if (dev_->id() == other.dev_->id() and
        owns_mem_) { // only then moving is possible
      free();
      shape_ = other.shape_;
      data_ = other.data_;
      dev_ = other.dev_;
      other.data_ = nullptr;
      other.shape_ = {0};
    } else { // otherwise defer back to copying
      *this = other;
    }
    return *this;
  }
  auto& operator+=(const Tensor<Scalar, Kind>& other) {
    *this += other.t();
    return *this;
  }

  // Construct by copying across devices
  template <DeviceKind OtherKind>
  Tensor(DevPtr<Kind> dev, const Tensor<Scalar, OtherKind>& other)
      : dev_(std::move(dev)), shape_(other.shape_) {
    allocate(size());
    copy(other.dev_, other.data_, size());
  }

  // Destroy
  ~Tensor() {
    if (owns_mem_) { free(); }
  }

  // Resize
  void resize(const Shape& shape) {
    if (size() != size(shape)) {
      if (size() == 0) {
        allocate(size(shape));
      } else {
        reallocate(size(shape));
      }
    }
    shape_ = shape;
  }

  // Convert to tensor with other Scalar type
  template <typename OtherScalar>
  Tensor<OtherScalar, Kind> cast() const {
    Tensor<OtherScalar, Kind> other(dev(), shape());
    other = t().template cast<Raw<OtherScalar>>();
    return other;
  }

  // TODO: maybe add these shorthands for all Scalar types
  Tensor<Real, Kind> real() const { return cast<Real>(); }

  // Views on Tensors

  // Reduce (by increasing or decreasing rank) shape to a given rank
  static Shape reduce(const Shape& shape, Size dim) {
    if (dim < (Size)shape.size()) {
      Size last = shape[dim - 1];
      for (Size i = shape.size() - 1; i >= dim; i--) { last *= shape[i]; }
      Shape new_shape(dim);
      for (Size i = 0; i < dim; i++) {
        new_shape[i] = (i == (dim - 1)) ? last : shape[i];
      }
      return new_shape;
    } else {
      Shape new_shape(shape);
      while ((Size)new_shape.size() < dim) { new_shape.push_back(1); }
      return new_shape;
    }
  }

  // Make this tensor a (possibly reshaped) non-memory-owning shallow copy
  // of the other
  auto& map(Tensor<Scalar, Kind>& other, const Shape& shape) {
    GINN_ASSERT(size(shape) == size(other.shape()));
    if (owns_mem_) { free(); }
    dev_ = other.dev_;
    data_ = other.data_;
    shape_ = shape;
    owns_mem_ = false;
    return *this;
  }

  // Make this tensor a (possibly reshaped) non-memory-owning shallow copy
  // of the other
  auto& map(Tensor<Scalar, Kind>& other) { return map(other, other.shape()); }

  // Make this tensor a non-memory-owning shallow copy of a subtensor
  // of the other
  auto& map(Tensor<Scalar, Kind>& other, Shape shape, Size offset) {
    GINN_ASSERT((size(shape) + offset) <= size(other.shape()));
    if (owns_mem_) { free(); }
    dev_ = other.dev_;
    data_ = other.data_ + offset;
    shape_ = shape;
    owns_mem_ = false;
    return *this;
  }

  // Return a possibly reshaped map (shallow, non-memory-owning copy) to this
  // tensor
  auto reshaped(const Shape& shape) {
    Tensor<Scalar, Kind> t;
    t.map(*this, shape);
    return t;
  }

  const Tensor<Scalar, Kind> reshaped(const Shape& shape) const {
    Tensor<Scalar, Kind> t;
    t.map(const_cast<Tensor<Scalar, Kind>&>(*this), shape);
    return t;
  }

  // TODO: Ditto for _only_ Kind==CPU

  // View as classical (CPU) Eigen matrix
  MatrixMap<Scalar> m() {
    GINN_ASSERT(dev()->kind() == CPU,
                "m() can only be invoked on Cpu tensors!");
    auto dims = reduce(shape_, 2);
    return MatrixMap<Scalar>(data_, dims[0], dims[1]);
  }
  ConstMatrixMap<Scalar> m() const {
    GINN_ASSERT(dev()->kind() == CPU,
                "m() can only be invoked on Cpu tensors!");
    auto dims = reduce(shape_, 2);
    return ConstMatrixMap<Scalar>(data_, dims[0], dims[1]);
  }

  VectorMap<Scalar> v() {
    GINN_ASSERT(dev()->kind() == CPU,
                "v() can only be invoked on Cpu tensors!");
    auto dims = reduce(shape_, 1);
    return VectorMap<Scalar>(data_, dims[0]);
  }
  ConstVectorMap<Scalar> v() const {
    GINN_ASSERT(dev()->kind() == CPU,
                "v() can only be invoked on Cpu tensors!");
    auto dims = reduce(shape_, 1);
    return ConstVectorMap<Scalar>(data_, dims[0]);
  }

  // begin() and end() help with feeding tensors into generic algorithms
  const RawScalar* begin() const {
    GINN_ASSERT(dev()->kind() == CPU,
                "begin() can only be invoked on Cpu tensors!");
    return data_;
  }

  const RawScalar* end() const {
    GINN_ASSERT(dev()->kind() == CPU,
                "end() can only be invoked on Cpu tensors!");
    return data_ + size();
  }

  std::vector<RawScalar> vector() const {
    auto t = copy_to(cpu());
    return std::vector<RawScalar>(t.begin(), t.end());
  }

  // wrap a Rank-0 (single element) Tensor around a scalar entry of this tensor
  auto operator()(Size i) {
    Tensor<Scalar, Kind> t;
    t.dev_ = dev_;
    t.shape_ = {}; // has to be rank 0
    t.owns_mem_ = false;
    t.data_ = data_ + i;
    return t;
  }

  auto operator()(Size i, Size j) {
    Tensor<Scalar, Kind> t;
    t.dev_ = dev_;
    t.shape_ = {}; // has to be rank 0
    t.owns_mem_ = false;
    t.data_ = data_ + i + j * rows();
    return t;
  }

  // View as tensor (Eigen / unsupported) with given rank
  template <size_t Rank>
  TensorMap<Scalar, Rank> view();
  template <size_t Rank>
  ConstTensorMap<Scalar, Rank> view() const;

  // View as rank 2 tensor
  TensorMap<Scalar, 2> t();
  ConstTensorMap<Scalar, 2> t() const;

  // This helper method is used to simplify device (CPU/GPU) based dispatching
  // of evaluators, such as :
  //     tensor.lhs() = ...   or
  //     tensor.lhs() += ...
  template <unsigned long R = 2>
  auto lhs() {
    return LhsExpr(view<R>(), dev());
  }

  template <unsigned long N>
  auto slice(const Index<N>& offsets, const Index<N>& sizes) {
    using LhsExprType = decltype(view<N>());
    return SliceExpr<LhsExprType, N, Kind>(dev(), view<N>(), offsets, sizes);
  }

  template <Size N>
  auto chip(Size offset, Size dim) {
    using LhsExprType = decltype(view<N>());
    return ChipExpr<LhsExprType, N, Kind>(dev(), view<N>(), offset, dim);
  }

  // Operator overloads for Eigen expressions to avoid having to use .lhs()
  // when possible
  template <typename RhsExpr>
  void operator=(RhsExpr e) {
    lhs<eigen::ndims<RhsExpr>()>() = e;
  }

  template <typename RhsExpr>
  void operator+=(RhsExpr e) {
    lhs<eigen::ndims<RhsExpr>()>() += e;
  }

  template <typename RhsExpr>
  void operator-=(RhsExpr e) {
    lhs<eigen::ndims<RhsExpr>()>() -= e;
  }

  Size rows() const { return reduce(shape_, 2)[0]; }
  Size cols() const { return reduce(shape_, 2)[1]; }
  Shape shape2() const { return reduce(shape_, 2); }
  void fill(RawScalar c) { lhs() = t().constant(c); }
  void set_zero() { fill(RawScalar{0}); }
  void set_ones() { fill(RawScalar{1}); }

  void set_random() {
    // TODO: making a copy here for now, get rid of this
    if constexpr (std::is_same_v<Scalar, Half> or std::is_same_v<Scalar, Int> or
                  std::is_same_v<Scalar, bool>) {
      // TODO: properly handle int and bool
      Tensor<Real, Kind> tmp(dev(), shape());
      tmp.set_random();
      *this = tmp.template cast<Scalar>();
    } else if constexpr (std::is_same_v<Scalar, Real>) {
      if (dev_->kind() == CPU) {
        m().setRandom();
      }
#ifdef GINN_ENABLE_GPU
      else if (dev_->kind() == GPU) {
        curand_gen(dev_->id().idx).uniform(data_, size());
        lhs() = -1 + (2 * t());
      }
#endif
      else {
        GINN_THROW("Unexpected device type!");
      }
    } else {
      GINN_THROW("Unexpected Scalar type!");
    }
  }

  template <typename RhsScalar>
  void set(const std::vector<RhsScalar>& vals) {
    std::vector<RawScalar> val(vals.begin(), vals.end());
    if (dev_->kind() == CPU) {
      auto v_ = v();
      auto s = std::min((size_t)v_.size(), val.size());
      for (size_t i = 0; i < s; i++) { v_[i] = val[i]; }
#ifdef GINN_ENABLE_GPU
    } else if (dev_->kind() == GPU) {
      Tensor<Scalar, CPU> tmp(cpu(), shape());
      tmp = *this;
      tmp.set(val);
      *this = tmp;
#endif
    } else {
      GINN_THROW("Unexpected device type!");
    }
  }

  template <typename... Args>
  void set(const Args&... args) {
    set(std::vector<RawScalar>{RawScalar(args)...});
  }

  template <int Rank, typename RhsScalar = RawScalar>
  void set(NestedInitList<Rank, RhsScalar> val) {
    resize(shape_of<Size, Rank, RhsScalar>(val));
    if (dev_->kind() == CPU) {
      assign<Rank, RawScalar, RhsScalar>(view<Rank>(), val);
#ifdef GINN_ENABLE_GPU
    } else if (dev_->kind() == GPU) {
      Tensor<Scalar, CPU> tmp(cpu(), shape());
      tmp.template set<Rank, RhsScalar>(val);
      *this = tmp;
#endif
    } else {
      GINN_THROW("Unexpected device type!");
    }
  }

  template <DeviceKind OtherKind>
  bool operator==(const Tensor<Scalar, OtherKind>& other) const {
    if (dev()->kind() == CPU) {
      if (other.dev()->kind() == CPU) {
        return shape_ == other.shape_ and v() == other.v();
      }
      Tensor<Scalar, CPU> other_cp(cpu());
      other_cp = other;
      return operator==(other_cp);
    }
    // TODO: compare gpu tensors without moving both to cpu
    Tensor<Scalar, CPU> cp(cpu());
    cp = *this;
    return cp == other;
  }

  void save(std::ostream& out) const {
    if (dev()->kind() == CPU) {
      out << shape_.size() << std::endl;
      for (Size dim : shape_) { out << dim << " "; }
      out << std::endl;
      for (Size i = 0; i < size(); i++) {
        if (i > 0) { out << " "; }
        out << data_[i];
      }
      out << std::endl;
    } else {
      Tensor<Scalar, CPU> cp(cpu());
      cp = *this;
      cp.save(out);
    }
  }

  void load(std::istream& in) {
    if (dev()->kind() == CPU) {
      Size r;
      in >> r;
      Shape new_shape(r);
      for (Size& dim : new_shape) { in >> dim; }
      resize(new_shape);
      for (Size i = 0; i < size(); i++) {
        double val;
        in >> val;
        data_[i] = RawScalar(val);
      }
      char end_of_line;
      in.get(end_of_line);
      GINN_ASSERT(end_of_line == '\n');
    } else {
      Tensor<Scalar, CPU> cp(cpu());
      cp.load(in);
      *this = cp;
    }
  }

  template <typename OtherScalar, DeviceKind Other>
  friend class Tensor;
};

template <typename Scalar, size_t... Indices>
auto view_impl(Raw<Scalar>* data,
               const Shape& shape,
               std::index_sequence<Indices...>) {
  if constexpr (sizeof...(Indices) == 0) {
    return TensorMap<Scalar, 0>(data);
  } /*else {*/
  auto dims = Tensor<Scalar, CPU>::reduce(shape, sizeof...(Indices));
  return TensorMap<Scalar, sizeof...(Indices)>(data, (dims[Indices])...);
  //}
}

template <typename Scalar, size_t... Indices>
auto const_view_impl(const Raw<Scalar>* data,
                     const Shape& shape,
                     std::index_sequence<Indices...>) {
  if constexpr (sizeof...(Indices) == 0) {
    return ConstTensorMap<Scalar, 0>(data);
  } /*else {*/
  auto dims = Tensor<Scalar, CPU>::reduce(shape, sizeof...(Indices));
  return ConstTensorMap<Scalar, sizeof...(Indices)>(data, (dims[Indices])...);
  //}
}

template <typename Scalar, DeviceKind Kind>
template <size_t Rank>
TensorMap<Scalar, Rank> Tensor<Scalar, Kind>::view() {
  return view_impl<Scalar>(data_, shape_, std::make_index_sequence<Rank>());
}

template <typename Scalar, DeviceKind Kind>
template <size_t Rank>
ConstTensorMap<Scalar, Rank> Tensor<Scalar, Kind>::view() const {
  return const_view_impl<Scalar>(
      data_, shape_, std::make_index_sequence<Rank>());
}

template <typename Scalar, DeviceKind Kind>
inline TensorMap<Scalar, 2> Tensor<Scalar, Kind>::t() {
  return view<2>();
}

template <typename Scalar, DeviceKind Kind>
inline ConstTensorMap<Scalar, 2> Tensor<Scalar, Kind>::t() const {
  return view<2>();
}

// Lefthandside expressions for Eigen expressions
//
// This helper class is used to simplify device (CPU/GPU) based dispatching
// of evaluators, such as :
//     Lhs(CPU, SomeEigenExpr) = OtherEigenExpr
//     Lhs(GPU, SomeEigenExpr) += OtherEigenExpr
// Lefthandside Expressions
template <typename InnerExpr, DeviceKind Kind>
class LhsExpr {
 public:
  InnerExpr e;
  DevPtr<Kind> dev;
  LhsExpr(InnerExpr a_e, DevPtr<Kind> a_dev) : e(a_e), dev(std::move(a_dev)) {}

#ifdef GINN_ENABLE_GPU
#define LHSEXPR_IMPLEMENT(op)                                                  \
  template <typename RhsExpr>                                                  \
  void op(RhsExpr rhs) {                                                       \
    if (dev->kind() == CPU) {                                                  \
      e.device(cpu_device()).op(rhs);                                          \
    } else if (dev->kind() == GPU) {                                           \
      auto& gd = gpu_device(dev->id().idx);                                    \
      GINN_CUDA_CALL(cudaSetDevice(dev->id().idx));                            \
      e.device(gd).op(rhs);                                                    \
    } else {                                                                   \
      GINN_THROW("Unexpected device!");                                        \
    }                                                                          \
  }
#else
#define LHSEXPR_IMPLEMENT(op)                                                  \
  template <typename RhsExpr>                                                  \
  void op(RhsExpr rhs) {                                                       \
    if (dev->kind() == CPU) {                                                  \
      e.device(cpu_device()).op(rhs);                                          \
    } else {                                                                   \
      GINN_THROW("Unexpected device!");                                        \
    }                                                                          \
  }
#endif

  LHSEXPR_IMPLEMENT(operator=)
  LHSEXPR_IMPLEMENT(operator+=)
  LHSEXPR_IMPLEMENT(operator-=)
};

template <typename InnerExpr, DeviceKind Kind>
auto Lhs(DevPtr<Kind> dev, InnerExpr e) {
  return LhsExpr<InnerExpr, Kind>(e, std::move(dev));
}

template <typename LhsExpr, Size N, DeviceKind Kind>
class SliceExpr {
 private:
  DevPtr<Kind> dev_;
  LhsExpr lhs_;
  Index<N> offsets_, sizes_;

 public:
  SliceExpr(DevPtr<Kind> dev, LhsExpr lhs, Index<N> offsets, Index<N> sizes)
      : dev_(std::move(dev)),
        lhs_(std::move(lhs)),
        offsets_(std::move(offsets)),
        sizes_(std::move(sizes)) {}
  template <typename RhsExpr>
  void operator=(RhsExpr rhs) {
    Lhs(dev_, lhs_.slice(offsets_, sizes_)) = rhs;
  }
  template <typename RhsExpr>
  void operator+=(RhsExpr rhs) {
    Lhs(dev_, lhs_.slice(offsets_, sizes_)) += rhs;
  }
}; // namespace ginn

template <typename LhsExpr, Size N, DeviceKind Kind>
class ChipExpr {
 private:
  DevPtr<Kind> dev_;
  LhsExpr lhs_;
  Size offset_, dim_;

 public:
  ChipExpr(DevPtr<Kind> dev, LhsExpr lhs, Size offset, Size dim)
      : dev_(std::move(dev)),
        lhs_(std::move(lhs)),
        offset_(offset),
        dim_(dim) {}
  template <typename RhsExpr>
  void operator=(RhsExpr rhs) {
    Lhs(dev_, lhs_.chip(offset_, dim_)) = rhs;
  }
  template <typename RhsExpr>
  void operator+=(RhsExpr rhs) {
    Lhs(dev_, lhs_.chip(offset_, dim_)) += rhs;
  }
};

} // end namespace ginn

#endif

# ginn::Tensor


 [More...](#detailed-description)

## Public Types

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| using ScalarType | **[Scalar](api/Classes/classginn_1_1_tensor.md#using-scalar)**  |


</span>

## Public Functions

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| DevPtr | **[dev](api/Classes/classginn_1_1_tensor.md#function-dev)**() const |
| Shape | **[shape](api/Classes/classginn_1_1_tensor.md#function-shape)**() const |
| Scalar * | **[data](api/Classes/classginn_1_1_tensor.md#function-data)**() |
| Size | **[size](api/Classes/classginn_1_1_tensor.md#function-size)**() const |
| auto & | **[move_to](api/Classes/classginn_1_1_tensor.md#function-move_to)**(const DevPtr & to) |
| auto | **[copy_to](api/Classes/classginn_1_1_tensor.md#function-copy_to)**(const DevPtr & to) const |
| auto | **[maybe_copy_to](api/Classes/classginn_1_1_tensor.md#function-maybe_copy_to)**(const DevPtr & to) |
| Scalar | **[item](api/Classes/classginn_1_1_tensor.md#function-item)**() const |
| | **[Tensor](api/Classes/classginn_1_1_tensor.md#function-tensor)**(DevPtr dev =cpu()) |
| | **[Tensor](api/Classes/classginn_1_1_tensor.md#function-tensor)**(DevPtr dev, Shape shape) |
| | **[Tensor](api/Classes/classginn_1_1_tensor.md#function-tensor)**(DevPtr dev, Shape shape, Scalar val) |
| | **[Tensor](api/Classes/classginn_1_1_tensor.md#function-tensor)**(Shape shape) |
| | **[Tensor](api/Classes/classginn_1_1_tensor.md#function-tensor)**(Shape shape, const std::vector< Scalar > & val) |
| | **[Tensor](api/Classes/classginn_1_1_tensor.md#function-tensor)**(DevPtr dev, Shape shape, std::vector< Scalar > val) |
| template <int Rank\> <br>| **[Tensor](api/Classes/classginn_1_1_tensor.md#function-tensor)**(DevPtr dev, NestedInitList< Rank, Scalar > val) |
| template <int Rank\> <br>| **[Tensor](api/Classes/classginn_1_1_tensor.md#function-tensor)**(NestedInitList< Rank, Scalar > val) |
| | **[Tensor](api/Classes/classginn_1_1_tensor.md#function-tensor)**(const [Tensor](api/Classes/classginn_1_1_tensor.md)< Scalar > & other) |
| | **[Tensor](api/Classes/classginn_1_1_tensor.md#function-tensor)**([Tensor](api/Classes/classginn_1_1_tensor.md)< Scalar > && other) |
| auto & | **[operator=](api/Classes/classginn_1_1_tensor.md#function-operator=)**(const [Tensor](api/Classes/classginn_1_1_tensor.md)< Scalar > & other) |
| auto & | **[operator=](api/Classes/classginn_1_1_tensor.md#function-operator=)**([Tensor](api/Classes/classginn_1_1_tensor.md)< Scalar > && other) |
| auto & | **[operator+=](api/Classes/classginn_1_1_tensor.md#function-operator+=)**(const [Tensor](api/Classes/classginn_1_1_tensor.md)< Scalar > & other) |
| | **[Tensor](api/Classes/classginn_1_1_tensor.md#function-tensor)**(DevPtr dev, const [Tensor](api/Classes/classginn_1_1_tensor.md)< Scalar > & other) |
| | **[~Tensor](api/Classes/classginn_1_1_tensor.md#function-~tensor)**() |
| void | **[resize](api/Classes/classginn_1_1_tensor.md#function-resize)**(const Shape & shape) |
| template <typename OtherScalar \> <br>[Tensor](api/Classes/classginn_1_1_tensor.md)< OtherScalar > | **[cast](api/Classes/classginn_1_1_tensor.md#function-cast)**() const |
| auto & | **[map](api/Classes/classginn_1_1_tensor.md#function-map)**([Tensor](api/Classes/classginn_1_1_tensor.md)< Scalar > & other, const Shape & shape) |
| auto & | **[map](api/Classes/classginn_1_1_tensor.md#function-map)**([Tensor](api/Classes/classginn_1_1_tensor.md)< Scalar > & other) |
| auto & | **[map](api/Classes/classginn_1_1_tensor.md#function-map)**([Tensor](api/Classes/classginn_1_1_tensor.md)< Scalar > & other, Shape shape, Size offset) |
| auto | **[reshaped](api/Classes/classginn_1_1_tensor.md#function-reshaped)**(const Shape & shape) |
| MatrixMap< Scalar > | **[m](api/Classes/classginn_1_1_tensor.md#function-m)**() |
| MatrixMap< Scalar > | **[m](api/Classes/classginn_1_1_tensor.md#function-m)**() const |
| VectorMap< Scalar > | **[v](api/Classes/classginn_1_1_tensor.md#function-v)**() |
| VectorMap< Scalar > | **[v](api/Classes/classginn_1_1_tensor.md#function-v)**() const |
| const Scalar * | **[begin](api/Classes/classginn_1_1_tensor.md#function-begin)**() const |
| const Scalar * | **[end](api/Classes/classginn_1_1_tensor.md#function-end)**() const |
| std::vector< Scalar > | **[vector](api/Classes/classginn_1_1_tensor.md#function-vector)**() const |
| auto | **[operator()](api/Classes/classginn_1_1_tensor.md#function-operator())**(Size i) |
| auto | **[operator()](api/Classes/classginn_1_1_tensor.md#function-operator())**(Size i, Size j) |
| template <size_t Rank\> <br>TensorMap< Scalar, Rank > | **[view](api/Classes/classginn_1_1_tensor.md#function-view)**() |
| template <size_t Rank\> <br>const TensorMap< Scalar, Rank > | **[view](api/Classes/classginn_1_1_tensor.md#function-view)**() const |
| TensorMap< Scalar, 2 > | **[t](api/Classes/classginn_1_1_tensor.md#function-t)**() |
| TensorMap< Scalar, 2 > const | **[t](api/Classes/classginn_1_1_tensor.md#function-t)**() const |
| template <unsigned long R =2\> <br>auto | **[lhs](api/Classes/classginn_1_1_tensor.md#function-lhs)**() |
| template <unsigned long N\> <br>auto | **[slice](api/Classes/classginn_1_1_tensor.md#function-slice)**(const Index< N > & offsets, const Index< N > & sizes) |
| template <Size N\> <br>auto | **[chip](api/Classes/classginn_1_1_tensor.md#function-chip)**(Size offset, Size dim) |
| template <typename RhsExpr \> <br>void | **[operator=](api/Classes/classginn_1_1_tensor.md#function-operator=)**(RhsExpr e) |
| template <typename RhsExpr \> <br>void | **[operator+=](api/Classes/classginn_1_1_tensor.md#function-operator+=)**(RhsExpr e) |
| template <typename RhsExpr \> <br>void | **[operator-=](api/Classes/classginn_1_1_tensor.md#function-operator-=)**(RhsExpr e) |
| Size | **[rows](api/Classes/classginn_1_1_tensor.md#function-rows)**() const |
| Size | **[cols](api/Classes/classginn_1_1_tensor.md#function-cols)**() const |
| Shape | **[shape2](api/Classes/classginn_1_1_tensor.md#function-shape2)**() const |
| void | **[fill](api/Classes/classginn_1_1_tensor.md#function-fill)**(Scalar c) |
| void | **[set_zero](api/Classes/classginn_1_1_tensor.md#function-set_zero)**() |
| void | **[set_ones](api/Classes/classginn_1_1_tensor.md#function-set_ones)**() |
| void | **[set_random](api/Classes/classginn_1_1_tensor.md#function-set_random)**() |
| template <typename RhsScalar \> <br>void | **[set](api/Classes/classginn_1_1_tensor.md#function-set)**(const std::vector< RhsScalar > & vals) |
| template <typename... Args\> <br>void | **[set](api/Classes/classginn_1_1_tensor.md#function-set)**(const [Args](api/Classes/classginn_1_1_args.md) &... args) |
| template <int Rank,typename RhsScalar  =Scalar\> <br>void | **[set](api/Classes/classginn_1_1_tensor.md#function-set)**(NestedInitList< Rank, RhsScalar > val) |
| bool | **[operator==](api/Classes/classginn_1_1_tensor.md#function-operator==)**(const [Tensor](api/Classes/classginn_1_1_tensor.md)< Scalar > & other) const |
| void | **[save](api/Classes/classginn_1_1_tensor.md#function-save)**(std::ostream & out) const |
| void | **[load](api/Classes/classginn_1_1_tensor.md#function-load)**(std::istream & in) |
| Size | **[size](api/Classes/classginn_1_1_tensor.md#function-size)**(const Shape & shape) |
| Shape | **[reduce](api/Classes/classginn_1_1_tensor.md#function-reduce)**(const Shape & shape, Size dim) |


</span>

## Detailed Description

```cpp
template <typename ScalarType  =Real>
class ginn::Tensor;
```

## Public Types Documentation

### using Scalar

```cpp
using ginn::Tensor< ScalarType >::Scalar =  ScalarType;
```


## Public Functions Documentation

### function dev

```cpp
inline DevPtr dev() const
```


### function shape

```cpp
inline Shape shape() const
```


### function data

```cpp
inline Scalar * data()
```


### function size

```cpp
inline Size size() const
```


### function move_to

```cpp
inline auto & move_to(
    const DevPtr & to
)
```


### function copy_to

```cpp
inline auto copy_to(
    const DevPtr & to
) const
```


### function maybe_copy_to

```cpp
inline auto maybe_copy_to(
    const DevPtr & to
)
```


### function item

```cpp
inline Scalar item() const
```


### function Tensor

```cpp
inline Tensor(
    DevPtr dev =cpu()
)
```


### function Tensor

```cpp
inline Tensor(
    DevPtr dev,
    Shape shape
)
```


### function Tensor

```cpp
inline Tensor(
    DevPtr dev,
    Shape shape,
    Scalar val
)
```


### function Tensor

```cpp
inline Tensor(
    Shape shape
)
```


### function Tensor

```cpp
inline Tensor(
    Shape shape,
    const std::vector< Scalar > & val
)
```


### function Tensor

```cpp
inline Tensor(
    DevPtr dev,
    Shape shape,
    std::vector< Scalar > val
)
```


### function Tensor

```cpp
template <int Rank>
inline Tensor(
    DevPtr dev,
    NestedInitList< Rank, Scalar > val
)
```


### function Tensor

```cpp
template <int Rank>
inline Tensor(
    NestedInitList< Rank, Scalar > val
)
```


### function Tensor

```cpp
inline Tensor(
    const Tensor< Scalar > & other
)
```


### function Tensor

```cpp
inline Tensor(
    Tensor< Scalar > && other
)
```


### function operator=

```cpp
inline auto & operator=(
    const Tensor< Scalar > & other
)
```


### function operator=

```cpp
inline auto & operator=(
    Tensor< Scalar > && other
)
```


### function operator+=

```cpp
inline auto & operator+=(
    const Tensor< Scalar > & other
)
```


### function Tensor

```cpp
inline Tensor(
    DevPtr dev,
    const Tensor< Scalar > & other
)
```


### function ~Tensor

```cpp
inline ~Tensor()
```


### function resize

```cpp
inline void resize(
    const Shape & shape
)
```


### function cast

```cpp
template <typename OtherScalar >
inline Tensor< OtherScalar > cast() const
```


### function map

```cpp
inline auto & map(
    Tensor< Scalar > & other,
    const Shape & shape
)
```


### function map

```cpp
inline auto & map(
    Tensor< Scalar > & other
)
```


### function map

```cpp
inline auto & map(
    Tensor< Scalar > & other,
    Shape shape,
    Size offset
)
```


### function reshaped

```cpp
inline auto reshaped(
    const Shape & shape
)
```


### function m

```cpp
inline MatrixMap< Scalar > m()
```


### function m

```cpp
inline MatrixMap< Scalar > m() const
```


### function v

```cpp
inline VectorMap< Scalar > v()
```


### function v

```cpp
inline VectorMap< Scalar > v() const
```


### function begin

```cpp
inline const Scalar * begin() const
```


### function end

```cpp
inline const Scalar * end() const
```


### function vector

```cpp
inline std::vector< Scalar > vector() const
```


### function operator()

```cpp
inline auto operator()(
    Size i
)
```


### function operator()

```cpp
inline auto operator()(
    Size i,
    Size j
)
```


### function view

```cpp
template <size_t Rank>
TensorMap< Scalar, Rank > view()
```


### function view

```cpp
template <size_t Rank>
const TensorMap< Scalar, Rank > view() const
```


### function t

```cpp
inline TensorMap< Scalar, 2 > t()
```


### function t

```cpp
inline TensorMap< Scalar, 2 > const t() const
```


### function lhs

```cpp
template <unsigned long R =2>
inline auto lhs()
```


### function slice

```cpp
template <unsigned long N>
inline auto slice(
    const Index< N > & offsets,
    const Index< N > & sizes
)
```


### function chip

```cpp
template <Size N>
inline auto chip(
    Size offset,
    Size dim
)
```


### function operator=

```cpp
template <typename RhsExpr >
inline void operator=(
    RhsExpr e
)
```


### function operator+=

```cpp
template <typename RhsExpr >
inline void operator+=(
    RhsExpr e
)
```


### function operator-=

```cpp
template <typename RhsExpr >
inline void operator-=(
    RhsExpr e
)
```


### function rows

```cpp
inline Size rows() const
```


### function cols

```cpp
inline Size cols() const
```


### function shape2

```cpp
inline Shape shape2() const
```


### function fill

```cpp
inline void fill(
    Scalar c
)
```


### function set_zero

```cpp
inline void set_zero()
```


### function set_ones

```cpp
inline void set_ones()
```


### function set_random

```cpp
inline void set_random()
```


### function set

```cpp
template <typename RhsScalar >
inline void set(
    const std::vector< RhsScalar > & vals
)
```


### function set

```cpp
template <typename... Args>
inline void set(
    const Args &... args
)
```


### function set

```cpp
template <int Rank,
typename RhsScalar  =Scalar>
inline void set(
    NestedInitList< Rank, RhsScalar > val
)
```


### function operator==

```cpp
inline bool operator==(
    const Tensor< Scalar > & other
) const
```


### function save

```cpp
inline void save(
    std::ostream & out
) const
```


### function load

```cpp
inline void load(
    std::istream & in
)
```


### function size

```cpp
static inline Size size(
    const Shape & shape
)
```


### function reduce

```cpp
static inline Shape reduce(
    const Shape & shape,
    Size dim
)
```


-------------------------------

Updated on 2022-12-24 at 15:34:35 -0500
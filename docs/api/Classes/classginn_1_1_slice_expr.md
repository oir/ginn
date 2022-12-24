# ginn::SliceExpr


 [More...](#detailed-description)

## Public Functions

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| | **[SliceExpr](api/Classes/classginn_1_1_slice_expr.md#function-sliceexpr)**(DevPtr dev, [LhsExpr](api/Classes/classginn_1_1_lhs_expr.md) lhs, Index< N > offsets, Index< N > sizes) |
| template <typename RhsExpr \> <br>void | **[operator=](api/Classes/classginn_1_1_slice_expr.md#function-operator=)**(RhsExpr rhs) |
| template <typename RhsExpr \> <br>void | **[operator+=](api/Classes/classginn_1_1_slice_expr.md#function-operator+=)**(RhsExpr rhs) |


</span>

## Detailed Description

```cpp
template <typename LhsExpr ,
Size N>
class ginn::SliceExpr;
```

## Public Functions Documentation

### function SliceExpr

```cpp
inline SliceExpr(
    DevPtr dev,
    LhsExpr lhs,
    Index< N > offsets,
    Index< N > sizes
)
```


### function operator=

```cpp
template <typename RhsExpr >
inline void operator=(
    RhsExpr rhs
)
```


### function operator+=

```cpp
template <typename RhsExpr >
inline void operator+=(
    RhsExpr rhs
)
```


-------------------------------

Updated on 2022-12-24 at 15:34:35 -0500
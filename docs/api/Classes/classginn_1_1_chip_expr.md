# ginn::ChipExpr


 [More...](#detailed-description)

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[ChipExpr](api/Classes/classginn_1_1_chip_expr.md#function-chipexpr)**(DevPtr dev, [LhsExpr](api/Classes/classginn_1_1_lhs_expr.md) lhs, Size offset, Size dim) |
| template <typename RhsExpr \> <br>void | **[operator=](api/Classes/classginn_1_1_chip_expr.md#function-operator=)**(RhsExpr rhs) |
| template <typename RhsExpr \> <br>void | **[operator+=](api/Classes/classginn_1_1_chip_expr.md#function-operator+=)**(RhsExpr rhs) |

## Detailed Description

```cpp
template <typename LhsExpr ,
Size N>
class ginn::ChipExpr;
```

## Public Functions Documentation

### function ChipExpr

```cpp
inline ChipExpr(
    DevPtr dev,
    LhsExpr lhs,
    Size offset,
    Size dim
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

Updated on 2022-12-24 at 14:52:49 -0500
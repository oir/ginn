# ginn::is_arithmetic


 [More...](#detailed-description)

## Public Attributes

|                | Name           |
| -------------- | -------------- |
| constexpr bool | **[value](api/Classes/structginn_1_1is__arithmetic.md#variable-value)**  |

## Detailed Description

```cpp
template <typename T >
struct ginn::is_arithmetic;
```

## Public Attributes Documentation

### variable value

```cpp
static constexpr bool value =
      std::is_arithmetic_v<T> or std::is_same_v<std::remove_cv_t<T>, Half>;
```


-------------------------------

Updated on 2022-12-24 at 14:52:49 -0500
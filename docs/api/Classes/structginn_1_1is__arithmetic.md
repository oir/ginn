# ginn::is_arithmetic


 [More...](#detailed-description)

## Public Attributes

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| constexpr bool | **[value](api/Classes/structginn_1_1is__arithmetic.md#variable-value)**  |


</span>

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

Updated on 2022-12-24 at 15:34:35 -0500
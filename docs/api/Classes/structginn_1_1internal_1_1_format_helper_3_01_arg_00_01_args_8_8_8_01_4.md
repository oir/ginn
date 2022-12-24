# ginn::internal::FormatHelper< Arg, Args... >


 [More...](#detailed-description)

## Public Functions

|                | Name           |
| -------------- | -------------- |
| template <typename... Args2\> <br>std::string | **[realize](api/Classes/structginn_1_1internal_1_1_format_helper_3_01_arg_00_01_args_8_8_8_01_4.md#function-realize)**(const Args2 &... args) const |
| | **[FormatHelper](api/Classes/structginn_1_1internal_1_1_format_helper_3_01_arg_00_01_args_8_8_8_01_4.md#function-formathelper)**([FormatHelper](api/Classes/structginn_1_1internal_1_1_format_helper.md)< Args... > head, const [Arg](api/Classes/classginn_1_1_arg.md) & arg) |
| | **[operator std::string](api/Classes/structginn_1_1internal_1_1_format_helper_3_01_arg_00_01_args_8_8_8_01_4.md#function-operator-stdstring)**() const |

## Public Attributes

|                | Name           |
| -------------- | -------------- |
| [FormatHelper](api/Classes/structginn_1_1internal_1_1_format_helper.md)< Args... > | **[head_](api/Classes/structginn_1_1internal_1_1_format_helper_3_01_arg_00_01_args_8_8_8_01_4.md#variable-head_)**  |
| member_t< [Arg](api/Classes/classginn_1_1_arg.md) > | **[arg_](api/Classes/structginn_1_1internal_1_1_format_helper_3_01_arg_00_01_args_8_8_8_01_4.md#variable-arg_)**  |

## Detailed Description

```cpp
template <typename Arg ,
typename... Args>
struct ginn::internal::FormatHelper< Arg, Args... >;
```

## Public Functions Documentation

### function realize

```cpp
template <typename... Args2>
inline std::string realize(
    const Args2 &... args
) const
```


### function FormatHelper

```cpp
inline FormatHelper(
    FormatHelper< Args... > head,
    const Arg & arg
)
```


### function operator std::string

```cpp
inline operator std::string() const
```


## Public Attributes Documentation

### variable head_

```cpp
FormatHelper< Args... > head_;
```


### variable arg_

```cpp
member_t< Arg > arg_;
```


-------------------------------

Updated on 2022-12-24 at 14:52:49 -0500
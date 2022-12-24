# ginn::internal


## Classes

|                | Name           |
| -------------- | -------------- |
| class | **[ginn::internal::ArgBase](api/Classes/classginn_1_1internal_1_1_arg_base.md)**  |
| class | **[ginn::internal::FileLines](api/Classes/classginn_1_1internal_1_1_file_lines.md)**  |
| struct | **[ginn::internal::FormatHelper](api/Classes/structginn_1_1internal_1_1_format_helper.md)**  |
| struct | **[ginn::internal::FormatHelper< Arg, Args... >](api/Classes/structginn_1_1internal_1_1_format_helper_3_01_arg_00_01_args_8_8_8_01_4.md)**  |
| struct | **[ginn::internal::MaybeValueType](api/Classes/structginn_1_1internal_1_1_maybe_value_type.md)**  |
| struct | **[ginn::internal::MaybeValueType< std::vector< T > >](api/Classes/structginn_1_1internal_1_1_maybe_value_type_3_01std_1_1vector_3_01_t_01_4_01_4.md)**  |
| struct | **[ginn::internal::MemberTypeHelper](api/Classes/structginn_1_1internal_1_1_member_type_helper.md)**  |
| struct | **[ginn::internal::MemberTypeHelper< char[N]>](api/Classes/structginn_1_1internal_1_1_member_type_helper_3_01char_0f_n_0e_4.md)**  |
| class | **[ginn::internal::TypedArgBase](api/Classes/classginn_1_1internal_1_1_typed_arg_base.md)**  |
| class | **[ginn::internal::Validator](api/Classes/classginn_1_1internal_1_1_validator.md)**  |

## Types

|                | Name           |
| -------------- | -------------- |
| template <typename T \> <br>using typename [MemberTypeHelper](api/Classes/structginn_1_1internal_1_1_member_type_helper.md)< T >::type | **[member_t](api/Namespaces/namespaceginn_1_1internal.md#using-member_t)**  |

## Functions

|                | Name           |
| -------------- | -------------- |
| template <typename Formatter \> <br>std::string | **[form](api/Namespaces/namespaceginn_1_1internal.md#function-form)**(Formatter f, const std::string & s) |
| template <typename T \> <br>std::string | **[default_meta](api/Namespaces/namespaceginn_1_1internal.md#function-default_meta)**() |
| template <typename Arg ,typename... Args\> <br>auto | **[operator,](api/Namespaces/namespaceginn_1_1internal.md#function-operator,)**([FormatHelper](api/Classes/structginn_1_1internal_1_1_format_helper.md)< Args... > head, const [Arg](api/Classes/classginn_1_1_arg.md) & arg) |
| template <typename... Args\> <br>std::ostream & | **[operator<<](api/Namespaces/namespaceginn_1_1internal.md#function-operator<<)**(std::ostream & out, const [FormatHelper](api/Classes/structginn_1_1internal_1_1_format_helper.md)< Args... > & fh) |
| template <typename T \> <br>auto | **[deep_copy](api/Namespaces/namespaceginn_1_1internal.md#function-deep_copy)**(const std::vector< std::shared_ptr< T > > & v) |
| template <typename T \> <br>auto | **[deep_copy](api/Namespaces/namespaceginn_1_1internal.md#function-deep_copy)**(const std::vector< T > & v) |
| template <typename T \> <br>auto | **[deep_copy](api/Namespaces/namespaceginn_1_1internal.md#function-deep_copy)**(const std::shared_ptr< T > & x) |
| template <typename T \> <br>auto | **[deep_copy](api/Namespaces/namespaceginn_1_1internal.md#function-deep_copy)**(const T & x) |
| bool | **[istty](api/Namespaces/namespaceginn_1_1internal.md#function-istty)**() |

## Types Documentation

### using member_t

```cpp
template <typename T >
using ginn::internal::member_t = typedef typename MemberTypeHelper<T>::type;
```



## Functions Documentation

### function form

```cpp
template <typename Formatter >
std::string form(
    Formatter f,
    const std::string & s
)
```


### function default_meta

```cpp
template <typename T >
inline std::string default_meta()
```


### function operator,

```cpp
template <typename Arg ,
typename... Args>
auto operator,(
    FormatHelper< Args... > head,
    const Arg & arg
)
```


### function operator<<

```cpp
template <typename... Args>
std::ostream & operator<<(
    std::ostream & out,
    const FormatHelper< Args... > & fh
)
```


### function deep_copy

```cpp
template <typename T >
auto deep_copy(
    const std::vector< std::shared_ptr< T > > & v
)
```


### function deep_copy

```cpp
template <typename T >
auto deep_copy(
    const std::vector< T > & v
)
```


### function deep_copy

```cpp
template <typename T >
auto deep_copy(
    const std::shared_ptr< T > & x
)
```


### function deep_copy

```cpp
template <typename T >
auto deep_copy(
    const T & x
)
```


### function istty

```cpp
bool istty()
```






-------------------------------

Updated on 2022-12-24 at 14:52:49 -0500
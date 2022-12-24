# ginn::internal::ArgBase




Inherited by [ginn::internal::TypedArgBase< bool >](api/Classes/classginn_1_1internal_1_1_typed_arg_base.md), [ginn::internal::TypedArgBase< std::vector< T > >](api/Classes/classginn_1_1internal_1_1_typed_arg_base.md), [ginn::internal::TypedArgBase< T >](api/Classes/classginn_1_1internal_1_1_typed_arg_base.md)

## Public Classes

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| struct | **[DefinitionError](api/Classes/structginn_1_1internal_1_1_arg_base_1_1_definition_error.md)**  |


</span>

## Protected Types

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| using fmt::terminal_color | **[Color](api/Classes/classginn_1_1internal_1_1_arg_base.md#using-color)**  |
| using fmt::emphasis | **[Emphasis](api/Classes/classginn_1_1internal_1_1_arg_base.md#using-emphasis)**  |


</span>

## Public Functions

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| virtual | **[~ArgBase](api/Classes/classginn_1_1internal_1_1_arg_base.md#function-~argbase)**() |
| | **[ArgBase](api/Classes/classginn_1_1internal_1_1_arg_base.md#function-argbase)**() =default |
| void | **[ensure](api/Classes/classginn_1_1internal_1_1_arg_base.md#function-ensure)**(bool predicate, const std::string & msg) |


</span>

## Protected Functions

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| std::string | **[color](api/Classes/classginn_1_1internal_1_1_arg_base.md#function-color)**(Color c, const std::string & s) const |
| std::string | **[emphasis](api/Classes/classginn_1_1internal_1_1_arg_base.md#function-emphasis)**(Emphasis e, const std::string & s) const |
| void | **[parse](api/Classes/classginn_1_1internal_1_1_arg_base.md#function-parse)**(const std::string & value) |
| virtual std::string | **[value](api/Classes/classginn_1_1internal_1_1_arg_base.md#function-value)**() const =0 |
| virtual std::string | **[help](api/Classes/classginn_1_1internal_1_1_arg_base.md#function-help)**() const |
| std::string | **[names](api/Classes/classginn_1_1internal_1_1_arg_base.md#function-names)**() const |
| std::string | **[usage](api/Classes/classginn_1_1internal_1_1_arg_base.md#function-usage)**() const |
| virtual bool | **[is_flag](api/Classes/classginn_1_1internal_1_1_arg_base.md#function-is_flag)**() const |
| virtual bool | **[is_nary](api/Classes/classginn_1_1internal_1_1_arg_base.md#function-is_nary)**() const |
| virtual std::unique_ptr< [ArgBase](api/Classes/classginn_1_1internal_1_1_arg_base.md) > | **[clone](api/Classes/classginn_1_1internal_1_1_arg_base.md#function-clone)**() const =0 |
| virtual void | **[parse_](api/Classes/classginn_1_1internal_1_1_arg_base.md#function-parse_)**(const std::string & value) =0 |


</span>

## Protected Attributes

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| std::string | **[help_](api/Classes/classginn_1_1internal_1_1_arg_base.md#variable-help_)**  |
| std::string | **[short_name_](api/Classes/classginn_1_1internal_1_1_arg_base.md#variable-short_name_)**  |
| std::string | **[long_name_](api/Classes/classginn_1_1internal_1_1_arg_base.md#variable-long_name_)**  |
| std::string | **[meta_](api/Classes/classginn_1_1internal_1_1_arg_base.md#variable-meta_)**  |
| bool | **[required_](api/Classes/classginn_1_1internal_1_1_arg_base.md#variable-required_)**  |
| bool | **[parsed_](api/Classes/classginn_1_1internal_1_1_arg_base.md#variable-parsed_)**  |
| bool | **[color_](api/Classes/classginn_1_1internal_1_1_arg_base.md#variable-color_)**  |


</span>

## Friends

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| class | **[ginn::Args](api/Classes/classginn_1_1internal_1_1_arg_base.md#friend-ginnargs)**  |


</span>

## Protected Types Documentation

### using Color

```cpp
using ginn::internal::ArgBase::Color =  fmt::terminal_color;
```


### using Emphasis

```cpp
using ginn::internal::ArgBase::Emphasis =  fmt::emphasis;
```


## Public Functions Documentation

### function ~ArgBase

```cpp
inline virtual ~ArgBase()
```


### function ArgBase

```cpp
ArgBase() =default
```


### function ensure

```cpp
static inline void ensure(
    bool predicate,
    const std::string & msg
)
```


## Protected Functions Documentation

### function color

```cpp
inline std::string color(
    Color c,
    const std::string & s
) const
```


### function emphasis

```cpp
inline std::string emphasis(
    Emphasis e,
    const std::string & s
) const
```


### function parse

```cpp
inline void parse(
    const std::string & value
)
```


### function value

```cpp
virtual std::string value() const =0
```


**Reimplemented by**: [ginn::Arg::value](api/Classes/classginn_1_1_arg.md#function-value), [ginn::Arg< bool >::value](api/Classes/classginn_1_1_arg_3_01bool_01_4.md#function-value), [ginn::Arg< std::vector< T > >::value](api/Classes/classginn_1_1_arg_3_01std_1_1vector_3_01_t_01_4_01_4.md#function-value)


### function help

```cpp
inline virtual std::string help() const
```


**Reimplemented by**: [ginn::internal::TypedArgBase::help](api/Classes/classginn_1_1internal_1_1_typed_arg_base.md#function-help), [ginn::internal::TypedArgBase::help](api/Classes/classginn_1_1internal_1_1_typed_arg_base.md#function-help), [ginn::internal::TypedArgBase::help](api/Classes/classginn_1_1internal_1_1_typed_arg_base.md#function-help), [ginn::Flag::help](api/Classes/classginn_1_1_flag.md#function-help)


### function names

```cpp
inline std::string names() const
```


### function usage

```cpp
inline std::string usage() const
```


### function is_flag

```cpp
inline virtual bool is_flag() const
```


**Reimplemented by**: [ginn::Flag::is_flag](api/Classes/classginn_1_1_flag.md#function-is_flag)


### function is_nary

```cpp
inline virtual bool is_nary() const
```


**Reimplemented by**: [ginn::Arg< std::vector< T > >::is_nary](api/Classes/classginn_1_1_arg_3_01std_1_1vector_3_01_t_01_4_01_4.md#function-is_nary)


### function clone

```cpp
virtual std::unique_ptr< ArgBase > clone() const =0
```


**Reimplemented by**: [ginn::Arg::clone](api/Classes/classginn_1_1_arg.md#function-clone), [ginn::Arg< bool >::clone](api/Classes/classginn_1_1_arg_3_01bool_01_4.md#function-clone), [ginn::Flag::clone](api/Classes/classginn_1_1_flag.md#function-clone), [ginn::Arg< std::vector< T > >::clone](api/Classes/classginn_1_1_arg_3_01std_1_1vector_3_01_t_01_4_01_4.md#function-clone)


### function parse_

```cpp
virtual void parse_(
    const std::string & value
) =0
```


**Reimplemented by**: [ginn::Flag::parse_](api/Classes/classginn_1_1_flag.md#function-parse_), [ginn::Arg::parse_](api/Classes/classginn_1_1_arg.md#function-parse_), [ginn::Arg< bool >::parse_](api/Classes/classginn_1_1_arg_3_01bool_01_4.md#function-parse_), [ginn::Arg< std::vector< T > >::parse_](api/Classes/classginn_1_1_arg_3_01std_1_1vector_3_01_t_01_4_01_4.md#function-parse_)


## Protected Attributes Documentation

### variable help_

```cpp
std::string help_;
```


### variable short_name_

```cpp
std::string short_name_;
```


### variable long_name_

```cpp
std::string long_name_;
```


### variable meta_

```cpp
std::string meta_;
```


### variable required_

```cpp
bool required_ = false;
```


### variable parsed_

```cpp
bool parsed_ = false;
```


### variable color_

```cpp
bool color_ = false;
```


## Friends

### friend ginn::Args

```cpp
friend class ginn::Args(
    ginn::Args 
);
```


-------------------------------

Updated on 2022-12-24 at 15:34:35 -0500
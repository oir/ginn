# ginn::Args




## Public Classes

|                | Name           |
| -------------- | -------------- |
| struct | **[ParseError](api/Classes/structginn_1_1_args_1_1_parse_error.md)**  |

## Public Types

|                | Name           |
| -------------- | -------------- |
| enum class| **[Color](api/Classes/classginn_1_1_args.md#enum-color)** { Auto, Always, Never} |
| using [internal::ArgBase](api/Classes/classginn_1_1internal_1_1_arg_base.md) | **[ArgBase](api/Classes/classginn_1_1_args.md#using-argbase)**  |

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[Args](api/Classes/classginn_1_1_args.md#function-args)**(std::string name ="", Color color =Color::Auto) |
| | **[Args](api/Classes/classginn_1_1_args.md#function-args)**(Color color, std::string name ="") |
| void | **[parse](api/Classes/classginn_1_1_args.md#function-parse)**(const std::vector< std::string > & argv) |
| void | **[parse](api/Classes/classginn_1_1_args.md#function-parse)**(int argc, char ** argv) |
| void | **[add_name](api/Classes/classginn_1_1_args.md#function-add_name)**(const std::string & name) |
| auto & | **[add](api/Classes/classginn_1_1_args.md#function-add)**(const [internal::ArgBase](api/Classes/classginn_1_1internal_1_1_arg_base.md) & arg) |
| auto & | **[operator()](api/Classes/classginn_1_1_args.md#function-operator())**(const [internal::ArgBase](api/Classes/classginn_1_1internal_1_1_arg_base.md) & arg) |
| void | **[add_help](api/Classes/classginn_1_1_args.md#function-add_help)**(bool has_help) |
| std::string | **[helpstr](api/Classes/classginn_1_1_args.md#function-helpstr)**() const |

## Public Types Documentation

### enum Color

| Enumerator | Value | Description |
| ---------- | ----- | ----------- |
| Auto | |   |
| Always | |   |
| Never | |   |




### using ArgBase

```cpp
using ginn::Args::ArgBase =  internal::ArgBase;
```


## Public Functions Documentation

### function Args

```cpp
inline Args(
    std::string name ="",
    Color color =Color::Auto
)
```


### function Args

```cpp
inline Args(
    Color color,
    std::string name =""
)
```


### function parse

```cpp
inline void parse(
    const std::vector< std::string > & argv
)
```


### function parse

```cpp
inline void parse(
    int argc,
    char ** argv
)
```


### function add_name

```cpp
inline void add_name(
    const std::string & name
)
```


### function add

```cpp
inline auto & add(
    const internal::ArgBase & arg
)
```


### function operator()

```cpp
inline auto & operator()(
    const internal::ArgBase & arg
)
```


### function add_help

```cpp
inline void add_help(
    bool has_help
)
```


### function helpstr

```cpp
inline std::string helpstr() const
```


-------------------------------

Updated on 2022-12-24 at 14:52:49 -0500
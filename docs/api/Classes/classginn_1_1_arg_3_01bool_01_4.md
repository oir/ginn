# ginn::Arg< bool >




Inherits from [ginn::internal::TypedArgBase< bool >](api/Classes/classginn_1_1internal_1_1_typed_arg_base.md), [ginn::internal::ArgBase](api/Classes/classginn_1_1internal_1_1_arg_base.md)

Inherited by [ginn::Flag](api/Classes/classginn_1_1_flag.md)

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[Arg](api/Classes/classginn_1_1_arg_3_01bool_01_4.md#function-arg)**(bool & dest) |
| virtual std::string | **[value](api/Classes/classginn_1_1_arg_3_01bool_01_4.md#function-value)**() const override |
| virtual std::unique_ptr< [internal::ArgBase](api/Classes/classginn_1_1internal_1_1_arg_base.md) > | **[clone](api/Classes/classginn_1_1_arg_3_01bool_01_4.md#function-clone)**() const override |

## Protected Functions

|                | Name           |
| -------------- | -------------- |
| virtual void | **[parse_](api/Classes/classginn_1_1_arg_3_01bool_01_4.md#function-parse_)**(const std::string & value) override |

## Additional inherited members

**Protected Types inherited from [ginn::internal::TypedArgBase< bool >](api/Classes/classginn_1_1internal_1_1_typed_arg_base.md)**

|                | Name           |
| -------------- | -------------- |
| using typename [MaybeValueType](api/Classes/structginn_1_1internal_1_1_maybe_value_type.md)< T >::type | **[value_t](api/Classes/classginn_1_1internal_1_1_typed_arg_base.md#using-value_t)**  |

**Public Functions inherited from [ginn::internal::TypedArgBase< bool >](api/Classes/classginn_1_1internal_1_1_typed_arg_base.md)**

|                | Name           |
| -------------- | -------------- |
| auto & | **[name](api/Classes/classginn_1_1internal_1_1_typed_arg_base.md#function-name)**(const std::string & s) |
| auto & | **[help](api/Classes/classginn_1_1internal_1_1_typed_arg_base.md#function-help)**(const std::string & s) |
| auto & | **[meta](api/Classes/classginn_1_1internal_1_1_typed_arg_base.md#function-meta)**(const std::string & s) |
| auto & | **[required](api/Classes/classginn_1_1internal_1_1_typed_arg_base.md#function-required)**(bool r =true) |
| auto & | **[suggest_range](api/Classes/classginn_1_1internal_1_1_typed_arg_base.md#function-suggest_range)**(value_t left, value_t right) |
| auto & | **[require_range](api/Classes/classginn_1_1internal_1_1_typed_arg_base.md#function-require_range)**(value_t left, value_t right) |
| template <typename Container \> <br>auto & | **[suggest_choices](api/Classes/classginn_1_1internal_1_1_typed_arg_base.md#function-suggest_choices)**(const Container & vals) |
| auto & | **[suggest_choices](api/Classes/classginn_1_1internal_1_1_typed_arg_base.md#function-suggest_choices)**(std::initializer_list< value_t > vals) |
| template <typename Container \> <br>auto & | **[require_choices](api/Classes/classginn_1_1internal_1_1_typed_arg_base.md#function-require_choices)**(const Container & vals) |
| auto & | **[require_choices](api/Classes/classginn_1_1internal_1_1_typed_arg_base.md#function-require_choices)**(std::initializer_list< value_t > vals) |

**Protected Functions inherited from [ginn::internal::TypedArgBase< bool >](api/Classes/classginn_1_1internal_1_1_typed_arg_base.md)**

|                | Name           |
| -------------- | -------------- |
| | **[TypedArgBase](api/Classes/classginn_1_1internal_1_1_typed_arg_base.md#function-typedargbase)**(T & dest) |
| virtual std::string | **[help](api/Classes/classginn_1_1internal_1_1_typed_arg_base.md#function-help)**() const override |

**Protected Attributes inherited from [ginn::internal::TypedArgBase< bool >](api/Classes/classginn_1_1internal_1_1_typed_arg_base.md)**

|                | Name           |
| -------------- | -------------- |
| T & | **[dest_](api/Classes/classginn_1_1internal_1_1_typed_arg_base.md#variable-dest_)**  |
| std::vector< [Validator](api/Classes/classginn_1_1internal_1_1_validator.md)< value_t > > | **[validators_](api/Classes/classginn_1_1internal_1_1_typed_arg_base.md#variable-validators_)**  |

**Friends inherited from [ginn::internal::TypedArgBase< bool >](api/Classes/classginn_1_1internal_1_1_typed_arg_base.md)**

|                | Name           |
| -------------- | -------------- |
| class | **[ginn::Args](api/Classes/classginn_1_1internal_1_1_typed_arg_base.md#friend-ginnargs)**  |

**Public Classes inherited from [ginn::internal::ArgBase](api/Classes/classginn_1_1internal_1_1_arg_base.md)**

|                | Name           |
| -------------- | -------------- |
| struct | **[DefinitionError](api/Classes/structginn_1_1internal_1_1_arg_base_1_1_definition_error.md)**  |

**Protected Types inherited from [ginn::internal::ArgBase](api/Classes/classginn_1_1internal_1_1_arg_base.md)**

|                | Name           |
| -------------- | -------------- |
| using fmt::terminal_color | **[Color](api/Classes/classginn_1_1internal_1_1_arg_base.md#using-color)**  |
| using fmt::emphasis | **[Emphasis](api/Classes/classginn_1_1internal_1_1_arg_base.md#using-emphasis)**  |

**Public Functions inherited from [ginn::internal::ArgBase](api/Classes/classginn_1_1internal_1_1_arg_base.md)**

|                | Name           |
| -------------- | -------------- |
| virtual | **[~ArgBase](api/Classes/classginn_1_1internal_1_1_arg_base.md#function-~argbase)**() |
| | **[ArgBase](api/Classes/classginn_1_1internal_1_1_arg_base.md#function-argbase)**() =default |
| void | **[ensure](api/Classes/classginn_1_1internal_1_1_arg_base.md#function-ensure)**(bool predicate, const std::string & msg) |

**Protected Functions inherited from [ginn::internal::ArgBase](api/Classes/classginn_1_1internal_1_1_arg_base.md)**

|                | Name           |
| -------------- | -------------- |
| std::string | **[color](api/Classes/classginn_1_1internal_1_1_arg_base.md#function-color)**(Color c, const std::string & s) const |
| std::string | **[emphasis](api/Classes/classginn_1_1internal_1_1_arg_base.md#function-emphasis)**(Emphasis e, const std::string & s) const |
| void | **[parse](api/Classes/classginn_1_1internal_1_1_arg_base.md#function-parse)**(const std::string & value) |
| virtual std::string | **[help](api/Classes/classginn_1_1internal_1_1_arg_base.md#function-help)**() const |
| std::string | **[names](api/Classes/classginn_1_1internal_1_1_arg_base.md#function-names)**() const |
| std::string | **[usage](api/Classes/classginn_1_1internal_1_1_arg_base.md#function-usage)**() const |
| virtual bool | **[is_flag](api/Classes/classginn_1_1internal_1_1_arg_base.md#function-is_flag)**() const |
| virtual bool | **[is_nary](api/Classes/classginn_1_1internal_1_1_arg_base.md#function-is_nary)**() const |

**Protected Attributes inherited from [ginn::internal::ArgBase](api/Classes/classginn_1_1internal_1_1_arg_base.md)**

|                | Name           |
| -------------- | -------------- |
| std::string | **[help_](api/Classes/classginn_1_1internal_1_1_arg_base.md#variable-help_)**  |
| std::string | **[short_name_](api/Classes/classginn_1_1internal_1_1_arg_base.md#variable-short_name_)**  |
| std::string | **[long_name_](api/Classes/classginn_1_1internal_1_1_arg_base.md#variable-long_name_)**  |
| std::string | **[meta_](api/Classes/classginn_1_1internal_1_1_arg_base.md#variable-meta_)**  |
| bool | **[required_](api/Classes/classginn_1_1internal_1_1_arg_base.md#variable-required_)**  |
| bool | **[parsed_](api/Classes/classginn_1_1internal_1_1_arg_base.md#variable-parsed_)**  |
| bool | **[color_](api/Classes/classginn_1_1internal_1_1_arg_base.md#variable-color_)**  |

**Friends inherited from [ginn::internal::ArgBase](api/Classes/classginn_1_1internal_1_1_arg_base.md)**

|                | Name           |
| -------------- | -------------- |
| class | **[ginn::Args](api/Classes/classginn_1_1internal_1_1_arg_base.md#friend-ginnargs)**  |


## Public Functions Documentation

### function Arg

```cpp
inline Arg(
    bool & dest
)
```


### function value

```cpp
inline virtual std::string value() const override
```


**Reimplements**: [ginn::internal::ArgBase::value](api/Classes/classginn_1_1internal_1_1_arg_base.md#function-value)


### function clone

```cpp
inline virtual std::unique_ptr< internal::ArgBase > clone() const override
```


**Reimplements**: [ginn::internal::ArgBase::clone](api/Classes/classginn_1_1internal_1_1_arg_base.md#function-clone)


**Reimplemented by**: [ginn::Flag::clone](api/Classes/classginn_1_1_flag.md#function-clone)


## Protected Functions Documentation

### function parse_

```cpp
inline virtual void parse_(
    const std::string & value
) override
```


**Reimplements**: [ginn::internal::ArgBase::parse_](api/Classes/classginn_1_1internal_1_1_arg_base.md#function-parse_)


**Reimplemented by**: [ginn::Flag::parse_](api/Classes/classginn_1_1_flag.md#function-parse_)


-------------------------------

Updated on 2022-12-24 at 14:52:49 -0500
# ginn::init::Uniform


 [More...](#detailed-description)

Inherits from [ginn::Initer< Scalar >](api/Classes/classginn_1_1_initer.md)

## Public Functions

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| template <typename RhsScalar  =Scalar\> <br>| **[Uniform](api/Classes/classginn_1_1init_1_1_uniform.md#function-uniform)**(RhsScalar range =RhsScalar(1.)) |
| virtual void | **[init](api/Classes/classginn_1_1init_1_1_uniform.md#function-init)**([Tensor](api/Classes/classginn_1_1_tensor.md)< Scalar > & w) override |


</span>

## Public Attributes

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| Scalar | **[range](api/Classes/classginn_1_1init_1_1_uniform.md#variable-range)**  |


</span>

## Additional inherited members

</span>

**Public Functions inherited from [ginn::Initer< Scalar >](api/Classes/classginn_1_1_initer.md)**

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| virtual | **[~Initer](api/Classes/classginn_1_1_initer.md#function-~initer)**() =default |


</span>


## Detailed Description

```cpp
template <typename Scalar >
class ginn::init::Uniform;
```

## Public Functions Documentation

### function Uniform

```cpp
template <typename RhsScalar  =Scalar>
inline Uniform(
    RhsScalar range =RhsScalar(1.)
)
```


### function init

```cpp
inline virtual void init(
    Tensor< Scalar > & w
) override
```


**Reimplements**: [ginn::Initer::init](api/Classes/classginn_1_1_initer.md#function-init)


## Public Attributes Documentation

### variable range

```cpp
Scalar range;
```


-------------------------------

Updated on 2022-12-24 at 15:34:35 -0500
# ginn::init::Xavier


 [More...](#detailed-description)

Inherits from [ginn::Initer< Scalar >](api/Classes/classginn_1_1_initer.md)

## Public Functions

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| | **[Xavier](api/Classes/classginn_1_1init_1_1_xavier.md#function-xavier)**() =default |
| virtual void | **[init](api/Classes/classginn_1_1init_1_1_xavier.md#function-init)**([Tensor](api/Classes/classginn_1_1_tensor.md)< Scalar > & w) override |


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
class ginn::init::Xavier;
```

## Public Functions Documentation

### function Xavier

```cpp
Xavier() =default
```


### function init

```cpp
inline virtual void init(
    Tensor< Scalar > & w
) override
```


**Reimplements**: [ginn::Initer::init](api/Classes/classginn_1_1_initer.md#function-init)


-------------------------------

Updated on 2022-12-24 at 15:34:35 -0500
# ginn::Initer


 [More...](#detailed-description)

Inherited by [ginn::init::Uniform< Scalar >](api/Classes/classginn_1_1init_1_1_uniform.md), [ginn::init::Xavier< Scalar >](api/Classes/classginn_1_1init_1_1_xavier.md), [ginn::init::Zero< Scalar >](api/Classes/classginn_1_1init_1_1_zero.md)

## Public Functions

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| virtual void | **[init](api/Classes/classginn_1_1_initer.md#function-init)**([Tensor](api/Classes/classginn_1_1_tensor.md)< Scalar > & w) =0 |
| void | **[init](api/Classes/classginn_1_1_initer.md#function-init)**(const [WeightPtr](api/Classes/classginn_1_1_ptr.md)< Scalar > & w) |
| void | **[init](api/Classes/classginn_1_1_initer.md#function-init)**(const std::vector< [WeightPtr](api/Classes/classginn_1_1_ptr.md)< Scalar > > & ws) |
| virtual | **[~Initer](api/Classes/classginn_1_1_initer.md#function-~initer)**() =default |


</span>

## Detailed Description

```cpp
template <typename Scalar >
class ginn::Initer;
```

## Public Functions Documentation

### function init

```cpp
virtual void init(
    Tensor< Scalar > & w
) =0
```


**Reimplemented by**: [ginn::init::Xavier::init](api/Classes/classginn_1_1init_1_1_xavier.md#function-init), [ginn::init::Uniform::init](api/Classes/classginn_1_1init_1_1_uniform.md#function-init), [ginn::init::Zero::init](api/Classes/classginn_1_1init_1_1_zero.md#function-init)


### function init

```cpp
inline void init(
    const WeightPtr< Scalar > & w
)
```


### function init

```cpp
inline void init(
    const std::vector< WeightPtr< Scalar > > & ws
)
```


### function ~Initer

```cpp
virtual ~Initer() =default
```


-------------------------------

Updated on 2022-12-24 at 15:34:35 -0500
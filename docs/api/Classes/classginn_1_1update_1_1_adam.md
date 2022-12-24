# ginn::update::Adam


 [More...](#detailed-description)

Inherits from [ginn::Updater< Scalar >](api/Classes/classginn_1_1_updater.md)

## Public Classes

|                | Name           |
| -------------- | -------------- |
| struct | **[History](api/Classes/structginn_1_1update_1_1_adam_1_1_history.md)**  |

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[Adam](api/Classes/classginn_1_1update_1_1_adam.md#function-adam)**(Real lr =1e-3, Real clip =5., Real eps =1e-8, Real beta_1 =0.9, Real beta_2 =0.999) |
| template <typename WeightPtr \> <br>void | **[init](api/Classes/classginn_1_1update_1_1_adam.md#function-init)**([WeightPtr](api/Classes/classginn_1_1_ptr.md) w) |
| template <typename WeightPtr \> <br>void | **[init](api/Classes/classginn_1_1update_1_1_adam.md#function-init)**(const std::vector< [WeightPtr](api/Classes/classginn_1_1_ptr.md) > & weights) |
| void | **[update](api/Classes/classginn_1_1update_1_1_adam.md#function-update)**([Tensor](api/Classes/classginn_1_1_tensor.md)< Scalar > & w, [Tensor](api/Classes/classginn_1_1_tensor.md)< Scalar > & d, size_t id) |
| virtual void | **[update](api/Classes/classginn_1_1update_1_1_adam.md#function-update)**(const [WeightPtr](api/Classes/classginn_1_1_ptr.md)< Scalar > & w) override |

## Public Attributes

|                | Name           |
| -------------- | -------------- |
| std::unordered_map< size_t, [History](api/Classes/structginn_1_1update_1_1_adam_1_1_history.md) > | **[weight_histories](api/Classes/classginn_1_1update_1_1_adam.md#variable-weight_histories)**  |
| std::mutex | **[history_access](api/Classes/classginn_1_1update_1_1_adam.md#variable-history_access)**  |
| Real | **[lr_](api/Classes/classginn_1_1update_1_1_adam.md#variable-lr_)**  |
| Real | **[eps_](api/Classes/classginn_1_1update_1_1_adam.md#variable-eps_)**  |
| Real | **[beta_1_](api/Classes/classginn_1_1update_1_1_adam.md#variable-beta_1_)**  |
| Real | **[beta_2_](api/Classes/classginn_1_1update_1_1_adam.md#variable-beta_2_)**  |
| Scalar | **[clip_](api/Classes/classginn_1_1update_1_1_adam.md#variable-clip_)**  |

## Additional inherited members

**Public Functions inherited from [ginn::Updater< Scalar >](api/Classes/classginn_1_1_updater.md)**

|                | Name           |
| -------------- | -------------- |
| virtual | **[~Updater](api/Classes/classginn_1_1_updater.md#function-~updater)**() =default |

**Public Attributes inherited from [ginn::Updater< Scalar >](api/Classes/classginn_1_1_updater.md)**

|                | Name           |
| -------------- | -------------- |
| bool | **[guard](api/Classes/classginn_1_1_updater.md#variable-guard)**  |


## Detailed Description

```cpp
template <typename Scalar >
class ginn::update::Adam;
```

## Public Functions Documentation

### function Adam

```cpp
inline Adam(
    Real lr =1e-3,
    Real clip =5.,
    Real eps =1e-8,
    Real beta_1 =0.9,
    Real beta_2 =0.999
)
```


### function init

```cpp
template <typename WeightPtr >
inline void init(
    WeightPtr w
)
```


### function init

```cpp
template <typename WeightPtr >
inline void init(
    const std::vector< WeightPtr > & weights
)
```


### function update

```cpp
inline void update(
    Tensor< Scalar > & w,
    Tensor< Scalar > & d,
    size_t id
)
```


### function update

```cpp
inline virtual void update(
    const WeightPtr< Scalar > & w
) override
```


**Reimplements**: [ginn::Updater::update](api/Classes/classginn_1_1_updater.md#function-update)


## Public Attributes Documentation

### variable weight_histories

```cpp
std::unordered_map< size_t, History > weight_histories;
```


### variable history_access

```cpp
std::mutex history_access;
```


### variable lr_

```cpp
Real lr_;
```


### variable eps_

```cpp
Real eps_;
```


### variable beta_1_

```cpp
Real beta_1_;
```


### variable beta_2_

```cpp
Real beta_2_;
```


### variable clip_

```cpp
Scalar clip_;
```


-------------------------------

Updated on 2022-12-24 at 14:52:49 -0500
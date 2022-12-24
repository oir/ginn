# ginn::update::Sgd


 [More...](#detailed-description)

Inherits from [ginn::Updater< Scalar >](api/Classes/classginn_1_1_updater.md)

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[Sgd](api/Classes/classginn_1_1update_1_1_sgd.md#function-sgd)**(Real a_lr =1e-1, Real a_clip =5.) |
| virtual void | **[update](api/Classes/classginn_1_1update_1_1_sgd.md#function-update)**(const [WeightPtr](api/Classes/classginn_1_1_ptr.md)< Scalar > & w) override |
| void | **[update](api/Classes/classginn_1_1update_1_1_sgd.md#function-update)**([Tensor](api/Classes/classginn_1_1_tensor.md)< Scalar > & w, [Tensor](api/Classes/classginn_1_1_tensor.md)< Scalar > & d) |

## Public Attributes

|                | Name           |
| -------------- | -------------- |
| Scalar | **[lr](api/Classes/classginn_1_1update_1_1_sgd.md#variable-lr)**  |
| Scalar | **[clip](api/Classes/classginn_1_1update_1_1_sgd.md#variable-clip)**  |

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
class ginn::update::Sgd;
```

## Public Functions Documentation

### function Sgd

```cpp
inline Sgd(
    Real a_lr =1e-1,
    Real a_clip =5.
)
```


### function update

```cpp
inline virtual void update(
    const WeightPtr< Scalar > & w
) override
```


**Reimplements**: [ginn::Updater::update](api/Classes/classginn_1_1_updater.md#function-update)


### function update

```cpp
inline void update(
    Tensor< Scalar > & w,
    Tensor< Scalar > & d
)
```


## Public Attributes Documentation

### variable lr

```cpp
Scalar lr;
```


### variable clip

```cpp
Scalar clip;
```


-------------------------------

Updated on 2022-12-24 at 14:52:49 -0500
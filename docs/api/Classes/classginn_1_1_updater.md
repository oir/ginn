# ginn::Updater


 [More...](#detailed-description)

Inherited by [ginn::update::Adam< Scalar >](api/Classes/classginn_1_1update_1_1_adam.md), [ginn::update::Sgd< Scalar >](api/Classes/classginn_1_1update_1_1_sgd.md)

## Public Functions

|                | Name           |
| -------------- | -------------- |
| virtual void | **[update](api/Classes/classginn_1_1_updater.md#function-update)**(const [WeightPtr](api/Classes/classginn_1_1_ptr.md)< Scalar > & ) =0 |
| void | **[update](api/Classes/classginn_1_1_updater.md#function-update)**(const std::vector< [WeightPtr](api/Classes/classginn_1_1_ptr.md)< Scalar > > & ws) |
| void | **[update](api/Classes/classginn_1_1_updater.md#function-update)**([Graph](api/Classes/classginn_1_1_graph.md) & g) |
| virtual | **[~Updater](api/Classes/classginn_1_1_updater.md#function-~updater)**() =default |

## Public Attributes

|                | Name           |
| -------------- | -------------- |
| bool | **[guard](api/Classes/classginn_1_1_updater.md#variable-guard)**  |

## Detailed Description

```cpp
template <typename Scalar >
class ginn::Updater;
```

## Public Functions Documentation

### function update

```cpp
virtual void update(
    const WeightPtr< Scalar > & 
) =0
```


**Reimplemented by**: [ginn::update::Sgd::update](api/Classes/classginn_1_1update_1_1_sgd.md#function-update), [ginn::update::Adam::update](api/Classes/classginn_1_1update_1_1_adam.md#function-update)


### function update

```cpp
inline void update(
    const std::vector< WeightPtr< Scalar > > & ws
)
```


### function update

```cpp
inline void update(
    Graph & g
)
```


### function ~Updater

```cpp
virtual ~Updater() =default
```


## Public Attributes Documentation

### variable guard

```cpp
bool guard = true;
```


-------------------------------

Updated on 2022-12-24 at 14:52:49 -0500
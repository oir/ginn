# ginn::LayerNodeBase




Inherited by [ginn::LayerNode< Out(In)>](api/Classes/classginn_1_1_layer_node_3_01_out_07_in_08_4.md)

## Public Functions

|                | Name           |
| -------------- | -------------- |
| virtual std::vector< [BaseNodePtr](api/Classes/classginn_1_1_ptr.md) > | **[weights_](api/Classes/classginn_1_1_layer_node_base.md#function-weights_)**() |
| template <typename Scalar \> <br>std::vector< [WeightPtr](api/Classes/classginn_1_1_ptr.md)< Scalar > > | **[weights](api/Classes/classginn_1_1_layer_node_base.md#function-weights)**() |
| virtual void | **[set_mode](api/Classes/classginn_1_1_layer_node_base.md#function-set_mode)**(Mode mode) |
| virtual Mode | **[mode](api/Classes/classginn_1_1_layer_node_base.md#function-mode)**() const |
| virtual | **[~LayerNodeBase](api/Classes/classginn_1_1_layer_node_base.md#function-~layernodebase)**() =default |

## Public Functions Documentation

### function weights_

```cpp
inline virtual std::vector< BaseNodePtr > weights_()
```


### function weights

```cpp
template <typename Scalar >
inline std::vector< WeightPtr< Scalar > > weights()
```


### function set_mode

```cpp
inline virtual void set_mode(
    Mode mode
)
```


### function mode

```cpp
inline virtual Mode mode() const
```


### function ~LayerNodeBase

```cpp
virtual ~LayerNodeBase() =default
```


-------------------------------

Updated on 2022-12-24 at 14:52:49 -0500
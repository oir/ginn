# ginn::TreeLstmLayerNode


 [More...](#detailed-description)

Inherits from [ginn::LayerNode< NodeTree< Real >(NodeTree< Real >)>](api/Classes/classginn_1_1_layer_node.md)

## Public Types

|                | Name           |
| -------------- | -------------- |
| using [TreeLstm](api/Classes/classginn_1_1_tree_lstm.md)< Scalar > | **[Model](api/Classes/classginn_1_1_tree_lstm_layer_node.md#using-model)**  |
| using typename Model::State | **[State](api/Classes/classginn_1_1_tree_lstm_layer_node.md#using-state)**  |
| using typename Model::Reduce | **[Reduce](api/Classes/classginn_1_1_tree_lstm_layer_node.md#using-reduce)**  |
| template <typename T \> <br>using [tree::Tree](api/Classes/classginn_1_1tree_1_1_tree.md)< T > | **[Tree](api/Classes/classginn_1_1_tree_lstm_layer_node.md#using-tree)**  |

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[TreeLstmLayerNode](api/Classes/classginn_1_1_tree_lstm_layer_node.md#function-treelstmlayernode)**() =default |
| | **[TreeLstmLayerNode](api/Classes/classginn_1_1_tree_lstm_layer_node.md#function-treelstmlayernode)**(DevPtr dev, Size labels, Size dim, Size xdim, Real drop_p =0., Reduce reduce =Reduce::add) |
| void | **[init](api/Classes/classginn_1_1_tree_lstm_layer_node.md#function-init)**(DevPtr dev, Size labels, Size dim, Size xdim, Real drop_p =0., Reduce reduce =Reduce::add) |
| std::vector< [BaseNodePtr](api/Classes/classginn_1_1_ptr.md) > | **[weights_](api/Classes/classginn_1_1_tree_lstm_layer_node.md#function-weights_)**() override |
| [NodeTree](api/Classes/classginn_1_1tree_1_1_tree.md)< Scalar > | **[run](api/Classes/classginn_1_1_tree_lstm_layer_node.md#function-run)**(const [NodeTree](api/Classes/classginn_1_1tree_1_1_tree.md)< Scalar > & x) override |
| LayerPtr< [NodeTree](api/Classes/classginn_1_1tree_1_1_tree.md)< Scalar >([NodeTree](api/Classes/classginn_1_1tree_1_1_tree.md)< Scalar >)> | **[copy](api/Classes/classginn_1_1_tree_lstm_layer_node.md#function-copy)**(Copy mode) override |

## Detailed Description

```cpp
template <typename Scalar  =Real>
class ginn::TreeLstmLayerNode;
```

## Public Types Documentation

### using Model

```cpp
using ginn::TreeLstmLayerNode< Scalar >::Model =  TreeLstm<Scalar>;
```


### using State

```cpp
using ginn::TreeLstmLayerNode< Scalar >::State =  typename Model::State;
```


### using Reduce

```cpp
using ginn::TreeLstmLayerNode< Scalar >::Reduce =  typename Model::Reduce;
```


### using Tree

```cpp
template <typename T >
using ginn::TreeLstmLayerNode< Scalar >::Tree =  tree::Tree<T>;
```


## Public Functions Documentation

### function TreeLstmLayerNode

```cpp
TreeLstmLayerNode() =default
```


### function TreeLstmLayerNode

```cpp
inline TreeLstmLayerNode(
    DevPtr dev,
    Size labels,
    Size dim,
    Size xdim,
    Real drop_p =0.,
    Reduce reduce =Reduce::add
)
```


### function init

```cpp
inline void init(
    DevPtr dev,
    Size labels,
    Size dim,
    Size xdim,
    Real drop_p =0.,
    Reduce reduce =Reduce::add
)
```


### function weights_

```cpp
inline std::vector< BaseNodePtr > weights_() override
```


### function run

```cpp
inline NodeTree< Scalar > run(
    const NodeTree< Scalar > & x
) override
```


### function copy

```cpp
inline LayerPtr< NodeTree< Scalar >(NodeTree< Scalar >)> copy(
    Copy mode
) override
```


-------------------------------

Updated on 2022-12-24 at 14:52:49 -0500
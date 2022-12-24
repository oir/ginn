# ginn::BiLstmLayerNode


 [More...](#detailed-description)

Inherits from [ginn::LayerNode< NodePtrs< Scalar >(NodePtrs< Scalar >)>](api/Classes/classginn_1_1_layer_node.md)

## Public Types

|                | Name           |
| -------------- | -------------- |
| using typename [Lstm](api/Classes/classginn_1_1_lstm.md)< Scalar >::State | **[State](api/Classes/classginn_1_1_bi_lstm_layer_node.md#using-state)**  |

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[BiLstmLayerNode](api/Classes/classginn_1_1_bi_lstm_layer_node.md#function-bilstmlayernode)**() =default |
| | **[BiLstmLayerNode](api/Classes/classginn_1_1_bi_lstm_layer_node.md#function-bilstmlayernode)**(DevPtr dev, Size dim, Size xdim, bool last =false, Real drop_p =0.) |
| void | **[init](api/Classes/classginn_1_1_bi_lstm_layer_node.md#function-init)**(DevPtr dev, Size dim, Size xdim) |
| NodePtrs< Scalar > | **[run](api/Classes/classginn_1_1_bi_lstm_layer_node.md#function-run)**(const NodePtrs< Scalar > & x) override |
| std::vector< [BaseNodePtr](api/Classes/classginn_1_1_ptr.md) > | **[weights_](api/Classes/classginn_1_1_bi_lstm_layer_node.md#function-weights_)**() override |
| LayerPtr< NodePtrs< Scalar >(NodePtrs< Scalar >)> | **[copy](api/Classes/classginn_1_1_bi_lstm_layer_node.md#function-copy)**(Copy mode) override |

## Detailed Description

```cpp
template <typename Scalar >
class ginn::BiLstmLayerNode;
```

## Public Types Documentation

### using State

```cpp
using ginn::BiLstmLayerNode< Scalar >::State =  typename Lstm<Scalar>::State;
```


## Public Functions Documentation

### function BiLstmLayerNode

```cpp
BiLstmLayerNode() =default
```


### function BiLstmLayerNode

```cpp
inline BiLstmLayerNode(
    DevPtr dev,
    Size dim,
    Size xdim,
    bool last =false,
    Real drop_p =0.
)
```


### function init

```cpp
inline void init(
    DevPtr dev,
    Size dim,
    Size xdim
)
```


### function run

```cpp
inline NodePtrs< Scalar > run(
    const NodePtrs< Scalar > & x
) override
```


### function weights_

```cpp
inline std::vector< BaseNodePtr > weights_() override
```


### function copy

```cpp
inline LayerPtr< NodePtrs< Scalar >(NodePtrs< Scalar >)> copy(
    Copy mode
) override
```


-------------------------------

Updated on 2022-12-24 at 14:52:49 -0500
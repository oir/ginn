# ginn::LstmLayerNode


 [More...](#detailed-description)

Inherits from [ginn::LayerNode< NodePtrs< Scalar >(NodePtrs< Scalar >)>](api/Classes/classginn_1_1_layer_node.md)

## Public Types

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| using typename [Lstm](api/Classes/classginn_1_1_lstm.md)< Scalar >::State | **[State](api/Classes/classginn_1_1_lstm_layer_node.md#using-state)**  |


</span>

## Public Functions

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| | **[LstmLayerNode](api/Classes/classginn_1_1_lstm_layer_node.md#function-lstmlayernode)**() =default |
| | **[LstmLayerNode](api/Classes/classginn_1_1_lstm_layer_node.md#function-lstmlayernode)**(DevPtr dev, Size dim, Size xdim, bool last =false, Real drop_p =0.) |
| void | **[init](api/Classes/classginn_1_1_lstm_layer_node.md#function-init)**(DevPtr dev, Size dim, Size xdim) |
| NodePtrs< Scalar > | **[run](api/Classes/classginn_1_1_lstm_layer_node.md#function-run)**(const NodePtrs< Scalar > & x) override |
| std::vector< [BaseNodePtr](api/Classes/classginn_1_1_ptr.md) > | **[weights_](api/Classes/classginn_1_1_lstm_layer_node.md#function-weights_)**() override |
| LayerPtr< NodePtrs< Scalar >(NodePtrs< Scalar >)> | **[copy](api/Classes/classginn_1_1_lstm_layer_node.md#function-copy)**(Copy mode) override |


</span>

## Detailed Description

```cpp
template <typename Scalar >
class ginn::LstmLayerNode;
```

## Public Types Documentation

### using State

```cpp
using ginn::LstmLayerNode< Scalar >::State =  typename Lstm<Scalar>::State;
```


## Public Functions Documentation

### function LstmLayerNode

```cpp
LstmLayerNode() =default
```


### function LstmLayerNode

```cpp
inline LstmLayerNode(
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

Updated on 2022-12-24 at 15:34:35 -0500
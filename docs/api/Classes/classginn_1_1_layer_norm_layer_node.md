# ginn::LayerNormLayerNode


 [More...](#detailed-description)

Inherits from [ginn::LayerNode< NodePtr< Scalar >(NodePtr< Scalar >)>](api/Classes/classginn_1_1_layer_node.md)

## Public Functions

|                | Name           |
| -------------- | -------------- |
| std::vector< [BaseNodePtr](api/Classes/classginn_1_1_ptr.md) > | **[weights_](api/Classes/classginn_1_1_layer_norm_layer_node.md#function-weights_)**() override |
| [NodePtr](api/Classes/classginn_1_1_ptr.md)< Scalar > | **[run](api/Classes/classginn_1_1_layer_norm_layer_node.md#function-run)**(const [NodePtr](api/Classes/classginn_1_1_ptr.md)< Scalar > & x) override |
| void | **[init](api/Classes/classginn_1_1_layer_norm_layer_node.md#function-init)**(DevPtr dev, Size dim) |
| | **[LayerNormLayerNode](api/Classes/classginn_1_1_layer_norm_layer_node.md#function-layernormlayernode)**() =default |
| | **[LayerNormLayerNode](api/Classes/classginn_1_1_layer_norm_layer_node.md#function-layernormlayernode)**(DevPtr dev, Size dim, bool inplace =false) |
| | **[LayerNormLayerNode](api/Classes/classginn_1_1_layer_norm_layer_node.md#function-layernormlayernode)**(const [LayerNormLayerNode](api/Classes/classginn_1_1_layer_norm_layer_node.md) & other) |
| LayerPtr< [NodePtr](api/Classes/classginn_1_1_ptr.md)< Scalar >([NodePtr](api/Classes/classginn_1_1_ptr.md)< Scalar >)> | **[copy](api/Classes/classginn_1_1_layer_norm_layer_node.md#function-copy)**(Copy mode) override |

## Public Attributes

|                | Name           |
| -------------- | -------------- |
| [WeightPtr](api/Classes/classginn_1_1_ptr.md)< Scalar > | **[gamma](api/Classes/classginn_1_1_layer_norm_layer_node.md#variable-gamma)**  |
| [WeightPtr](api/Classes/classginn_1_1_ptr.md)< Scalar > | **[beta](api/Classes/classginn_1_1_layer_norm_layer_node.md#variable-beta)**  |
| bool | **[inplace_](api/Classes/classginn_1_1_layer_norm_layer_node.md#variable-inplace_)**  |

## Detailed Description

```cpp
template <typename Scalar >
class ginn::LayerNormLayerNode;
```

## Public Functions Documentation

### function weights_

```cpp
inline std::vector< BaseNodePtr > weights_() override
```


### function run

```cpp
inline NodePtr< Scalar > run(
    const NodePtr< Scalar > & x
) override
```


### function init

```cpp
inline void init(
    DevPtr dev,
    Size dim
)
```


### function LayerNormLayerNode

```cpp
LayerNormLayerNode() =default
```


### function LayerNormLayerNode

```cpp
inline LayerNormLayerNode(
    DevPtr dev,
    Size dim,
    bool inplace =false
)
```


### function LayerNormLayerNode

```cpp
inline LayerNormLayerNode(
    const LayerNormLayerNode & other
)
```


### function copy

```cpp
inline LayerPtr< NodePtr< Scalar >(NodePtr< Scalar >)> copy(
    Copy mode
) override
```


## Public Attributes Documentation

### variable gamma

```cpp
WeightPtr< Scalar > gamma = nullptr;
```


### variable beta

```cpp
WeightPtr< Scalar > beta = nullptr;
```


### variable inplace_

```cpp
bool inplace_ = false;
```


-------------------------------

Updated on 2022-12-24 at 14:52:49 -0500
# ginn::AffineLayerNode


 [More...](#detailed-description)

Inherits from [ginn::LayerNode< NodePtr< Scalar >(NodePtr< Scalar >)>](api/Classes/classginn_1_1_layer_node.md)

## Public Functions

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| | **[AffineLayerNode](api/Classes/classginn_1_1_affine_layer_node.md#function-affinelayernode)**() |
| template <typename Nonlin \> <br>| **[AffineLayerNode](api/Classes/classginn_1_1_affine_layer_node.md#function-affinelayernode)**(DevPtr dev, Nonlin nonlin, Size dim, Size xdim) |
| | **[AffineLayerNode](api/Classes/classginn_1_1_affine_layer_node.md#function-affinelayernode)**(const [AffineLayerNode](api/Classes/classginn_1_1_affine_layer_node.md)< Scalar > & other) |
| LayerPtr< [NodePtr](api/Classes/classginn_1_1_ptr.md)< Scalar >([NodePtr](api/Classes/classginn_1_1_ptr.md)< Scalar >)> | **[copy](api/Classes/classginn_1_1_affine_layer_node.md#function-copy)**(Copy mode) override |
| void | **[init](api/Classes/classginn_1_1_affine_layer_node.md#function-init)**(DevPtr dev, Size dim, Size xdim) |
| [NodePtr](api/Classes/classginn_1_1_ptr.md)< Scalar > | **[run](api/Classes/classginn_1_1_affine_layer_node.md#function-run)**(const [NodePtr](api/Classes/classginn_1_1_ptr.md)< Scalar > & x) override |
| std::vector< [BaseNodePtr](api/Classes/classginn_1_1_ptr.md) > | **[weights_](api/Classes/classginn_1_1_affine_layer_node.md#function-weights_)**() override |


</span>

## Public Attributes

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| [WeightPtr](api/Classes/classginn_1_1_ptr.md)< Scalar > | **[W](api/Classes/classginn_1_1_affine_layer_node.md#variable-w)**  |
| [WeightPtr](api/Classes/classginn_1_1_ptr.md)< Scalar > | **[b](api/Classes/classginn_1_1_affine_layer_node.md#variable-b)**  |
| std::unique_ptr< [NonlinOp](api/Classes/classginn_1_1_nonlin_op.md)< Scalar > > | **[nonlin](api/Classes/classginn_1_1_affine_layer_node.md#variable-nonlin)**  |


</span>

## Detailed Description

```cpp
template <typename Scalar >
class ginn::AffineLayerNode;
```

## Public Functions Documentation

### function AffineLayerNode

```cpp
inline AffineLayerNode()
```


### function AffineLayerNode

```cpp
template <typename Nonlin >
inline AffineLayerNode(
    DevPtr dev,
    Nonlin nonlin,
    Size dim,
    Size xdim
)
```


### function AffineLayerNode

```cpp
inline AffineLayerNode(
    const AffineLayerNode< Scalar > & other
)
```


### function copy

```cpp
inline LayerPtr< NodePtr< Scalar >(NodePtr< Scalar >)> copy(
    Copy mode
) override
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
inline NodePtr< Scalar > run(
    const NodePtr< Scalar > & x
) override
```


### function weights_

```cpp
inline std::vector< BaseNodePtr > weights_() override
```


## Public Attributes Documentation

### variable W

```cpp
WeightPtr< Scalar > W;
```


### variable b

```cpp
WeightPtr< Scalar > b;
```


### variable nonlin

```cpp
std::unique_ptr< NonlinOp< Scalar > > nonlin;
```


-------------------------------

Updated on 2022-12-24 at 15:34:35 -0500
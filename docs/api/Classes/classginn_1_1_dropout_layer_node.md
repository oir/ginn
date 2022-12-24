# ginn::DropoutLayerNode


 [More...](#detailed-description)

Inherits from [ginn::LayerNode< NodePtr< Scalar >(NodePtr< Scalar >)>](api/Classes/classginn_1_1_layer_node.md)

## Public Functions

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| [NodePtr](api/Classes/classginn_1_1_ptr.md)< Scalar > | **[run](api/Classes/classginn_1_1_dropout_layer_node.md#function-run)**(const [NodePtr](api/Classes/classginn_1_1_ptr.md)< Scalar > & x) override |
| | **[DropoutLayerNode](api/Classes/classginn_1_1_dropout_layer_node.md#function-dropoutlayernode)**() =default |
| | **[DropoutLayerNode](api/Classes/classginn_1_1_dropout_layer_node.md#function-dropoutlayernode)**(Real drop_p, bool inplace =false) |
| | **[DropoutLayerNode](api/Classes/classginn_1_1_dropout_layer_node.md#function-dropoutlayernode)**(const [DropoutLayerNode](api/Classes/classginn_1_1_dropout_layer_node.md) & other) =default |
| LayerPtr< [NodePtr](api/Classes/classginn_1_1_ptr.md)< Scalar >([NodePtr](api/Classes/classginn_1_1_ptr.md)< Scalar >)> | **[copy](api/Classes/classginn_1_1_dropout_layer_node.md#function-copy)**(Copy ) override |


</span>

## Detailed Description

```cpp
template <typename Scalar >
class ginn::DropoutLayerNode;
```

## Public Functions Documentation

### function run

```cpp
inline NodePtr< Scalar > run(
    const NodePtr< Scalar > & x
) override
```


### function DropoutLayerNode

```cpp
DropoutLayerNode() =default
```


### function DropoutLayerNode

```cpp
inline DropoutLayerNode(
    Real drop_p,
    bool inplace =false
)
```


### function DropoutLayerNode

```cpp
DropoutLayerNode(
    const DropoutLayerNode & other
) =default
```


### function copy

```cpp
inline LayerPtr< NodePtr< Scalar >(NodePtr< Scalar >)> copy(
    Copy 
) override
```


-------------------------------

Updated on 2022-12-24 at 15:34:35 -0500
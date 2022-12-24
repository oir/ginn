# ginn::CatLayerNode


 [More...](#detailed-description)

Inherits from [ginn::LayerNode< NodePtr< Scalar >(NodePtrPair< Scalar >)>](api/Classes/classginn_1_1_layer_node.md)

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[CatLayerNode](api/Classes/classginn_1_1_cat_layer_node.md#function-catlayernode)**() =default |
| LayerPtr< [NodePtr](api/Classes/classginn_1_1_ptr.md)< Scalar >(NodePtrPair< Scalar >)> | **[copy](api/Classes/classginn_1_1_cat_layer_node.md#function-copy)**(Copy ) override |
| [NodePtr](api/Classes/classginn_1_1_ptr.md)< Scalar > | **[run](api/Classes/classginn_1_1_cat_layer_node.md#function-run)**(const NodePtrPair< Scalar > & xs) override |

## Detailed Description

```cpp
template <typename Scalar >
class ginn::CatLayerNode;
```

## Public Functions Documentation

### function CatLayerNode

```cpp
CatLayerNode() =default
```


### function copy

```cpp
inline LayerPtr< NodePtr< Scalar >(NodePtrPair< Scalar >)> copy(
    Copy 
) override
```


### function run

```cpp
inline NodePtr< Scalar > run(
    const NodePtrPair< Scalar > & xs
) override
```


-------------------------------

Updated on 2022-12-24 at 14:52:49 -0500
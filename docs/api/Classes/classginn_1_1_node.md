# ginn::Node


 [More...](#detailed-description)

Inherits from [ginn::BaseNode](api/Classes/classginn_1_1_base_node.md)

Inherited by [ginn::BaseDataNode< Real >](api/Classes/classginn_1_1_base_data_node.md), [ginn::BaseDataNode< bool >](api/Classes/classginn_1_1_base_data_node.md), [ginn::BaseDataNode< Scalar >](api/Classes/classginn_1_1_base_data_node.md), [ginn::WeightNode< Scalar >](api/Classes/classginn_1_1_weight_node.md)

## Public Types

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| using ScalarType | **[Scalar](api/Classes/classginn_1_1_node.md#using-scalar)**  |


</span>

## Public Functions

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| virtual const [Tensor](api/Classes/classginn_1_1_tensor.md)< Scalar > & | **[value](api/Classes/classginn_1_1_node.md#function-value)**() const =0 |
| virtual const [Tensor](api/Classes/classginn_1_1_tensor.md)< Scalar > & | **[grad](api/Classes/classginn_1_1_node.md#function-grad)**() const =0 |
| [Tensor](api/Classes/classginn_1_1_tensor.md)< Scalar > & | **[value](api/Classes/classginn_1_1_node.md#function-value)**() |
| [Tensor](api/Classes/classginn_1_1_tensor.md)< Scalar > & | **[grad](api/Classes/classginn_1_1_node.md#function-grad)**() |
| virtual DevPtr | **[dev](api/Classes/classginn_1_1_node.md#function-dev)**() const override |
| virtual Shape | **[shape](api/Classes/classginn_1_1_node.md#function-shape)**() const override |
| virtual void | **[init_grad](api/Classes/classginn_1_1_node.md#function-init_grad)**() override |
| virtual void | **[reset_grad](api/Classes/classginn_1_1_node.md#function-reset_grad)**() override |
| Scalar | **[item](api/Classes/classginn_1_1_node.md#function-item)**() const |
| | **[BaseNode](api/Classes/classginn_1_1_node.md#function-basenode)**() =default |
| | **[BaseNode](api/Classes/classginn_1_1_node.md#function-basenode)**(const std::vector< [BaseNodePtr](api/Classes/classginn_1_1_ptr.md) > & ins) |
| template <typename Container \> <br>| **[BaseNode](api/Classes/classginn_1_1_node.md#function-basenode)**(const Container & ins) |


</span>

## Additional inherited members

</span>

**Public Functions inherited from [ginn::BaseNode](api/Classes/classginn_1_1_base_node.md)**

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| const auto & | **[ins](api/Classes/classginn_1_1_base_node.md#function-ins)**() |
| std::vector< [ConstBaseNodePtr](api/Classes/classginn_1_1_ptr.md) > | **[ins](api/Classes/classginn_1_1_base_node.md#function-ins)**() const |
| const [BaseNodePtr](api/Classes/classginn_1_1_ptr.md) & | **[in](api/Classes/classginn_1_1_base_node.md#function-in)**(size_t idx =0) |
| [ConstBaseNodePtr](api/Classes/classginn_1_1_ptr.md) | **[in](api/Classes/classginn_1_1_base_node.md#function-in)**(size_t idx =0) const |
| virtual void | **[set_ins](api/Classes/classginn_1_1_base_node.md#function-set_ins)**(const std::vector< [BaseNodePtr](api/Classes/classginn_1_1_ptr.md) > & ) |
| virtual | **[~BaseNode](api/Classes/classginn_1_1_base_node.md#function-~basenode)**() =default |
| Shape | **[shape2](api/Classes/classginn_1_1_base_node.md#function-shape2)**() const |
| Size | **[rows](api/Classes/classginn_1_1_base_node.md#function-rows)**() const |
| Size | **[cols](api/Classes/classginn_1_1_base_node.md#function-cols)**() const |
| Size | **[size](api/Classes/classginn_1_1_base_node.md#function-size)**() const |
| void | **[forward](api/Classes/classginn_1_1_base_node.md#function-forward)**() |
| void | **[backward](api/Classes/classginn_1_1_base_node.md#function-backward)**() |
| virtual bool | **[has_grad](api/Classes/classginn_1_1_base_node.md#function-has_grad)**() const |
| virtual void | **[reset_forwarded](api/Classes/classginn_1_1_base_node.md#function-reset_forwarded)**() |
| virtual std::string | **[name](api/Classes/classginn_1_1_base_node.md#function-name)**() const =0 |


</span>

**Protected Functions inherited from [ginn::BaseNode](api/Classes/classginn_1_1_base_node.md)**

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| virtual void | **[forward_](api/Classes/classginn_1_1_base_node.md#function-forward_)**() |
| virtual void | **[backward_](api/Classes/classginn_1_1_base_node.md#function-backward_)**() |


</span>

**Public Attributes inherited from [ginn::BaseNode](api/Classes/classginn_1_1_base_node.md)**

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| bool | **[forwarded](api/Classes/classginn_1_1_base_node.md#variable-forwarded)**  |


</span>

**Protected Attributes inherited from [ginn::BaseNode](api/Classes/classginn_1_1_base_node.md)**

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| std::vector< [BaseNodePtr](api/Classes/classginn_1_1_ptr.md) > | **[ins_](api/Classes/classginn_1_1_base_node.md#variable-ins_)**  |


</span>


## Detailed Description

```cpp
template <typename ScalarType  =Real>
class ginn::Node;
```

## Public Types Documentation

### using Scalar

```cpp
using ginn::Node< ScalarType >::Scalar =  ScalarType;
```


## Public Functions Documentation

### function value

```cpp
virtual const Tensor< Scalar > & value() const =0
```


**Reimplemented by**: [ginn::BaseDataNode::value](api/Classes/classginn_1_1_base_data_node.md#function-value), [ginn::BaseDataNode::value](api/Classes/classginn_1_1_base_data_node.md#function-value), [ginn::BaseDataNode::value](api/Classes/classginn_1_1_base_data_node.md#function-value), [ginn::BaseDataNode::value](api/Classes/classginn_1_1_base_data_node.md#function-value), [ginn::InPlaceAddNode::value](api/Classes/classginn_1_1_in_place_add_node.md#function-value), [ginn::InPlaceAddScalarNode::value](api/Classes/classginn_1_1_in_place_add_scalar_node.md#function-value), [ginn::InPlaceCwiseProdNode::value](api/Classes/classginn_1_1_in_place_cwise_prod_node.md#function-value), [ginn::InPlaceProdScalarNode::value](api/Classes/classginn_1_1_in_place_prod_scalar_node.md#function-value), [ginn::InPlaceDropoutNode::value](api/Classes/classginn_1_1_in_place_dropout_node.md#function-value), [ginn::InPlaceMaskNode::value](api/Classes/classginn_1_1_in_place_mask_node.md#function-value), [ginn::InPlaceLayerNormNode::value](api/Classes/classginn_1_1_in_place_layer_norm_node.md#function-value), [ginn::DeviceViewNode::value](api/Classes/classginn_1_1_device_view_node.md#function-value), [ginn::MapNode::value](api/Classes/classginn_1_1_map_node.md#function-value), [ginn::WeightNode::value](api/Classes/classginn_1_1_weight_node.md#function-value)


### function grad

```cpp
virtual const Tensor< Scalar > & grad() const =0
```


**Reimplemented by**: [ginn::BaseDataNode::grad](api/Classes/classginn_1_1_base_data_node.md#function-grad), [ginn::BaseDataNode::grad](api/Classes/classginn_1_1_base_data_node.md#function-grad), [ginn::BaseDataNode::grad](api/Classes/classginn_1_1_base_data_node.md#function-grad), [ginn::BaseDataNode::grad](api/Classes/classginn_1_1_base_data_node.md#function-grad), [ginn::InPlaceAddNode::grad](api/Classes/classginn_1_1_in_place_add_node.md#function-grad), [ginn::InPlaceAddScalarNode::grad](api/Classes/classginn_1_1_in_place_add_scalar_node.md#function-grad), [ginn::InPlaceCwiseProdNode::grad](api/Classes/classginn_1_1_in_place_cwise_prod_node.md#function-grad), [ginn::InPlaceProdScalarNode::grad](api/Classes/classginn_1_1_in_place_prod_scalar_node.md#function-grad), [ginn::InPlaceDropoutNode::grad](api/Classes/classginn_1_1_in_place_dropout_node.md#function-grad), [ginn::InPlaceMaskNode::grad](api/Classes/classginn_1_1_in_place_mask_node.md#function-grad), [ginn::InPlaceLayerNormNode::grad](api/Classes/classginn_1_1_in_place_layer_norm_node.md#function-grad), [ginn::DeviceViewNode::grad](api/Classes/classginn_1_1_device_view_node.md#function-grad), [ginn::MapNode::grad](api/Classes/classginn_1_1_map_node.md#function-grad), [ginn::WeightNode::grad](api/Classes/classginn_1_1_weight_node.md#function-grad)


### function value

```cpp
inline Tensor< Scalar > & value()
```


### function grad

```cpp
inline Tensor< Scalar > & grad()
```


### function dev

```cpp
inline virtual DevPtr dev() const override
```


**Reimplements**: [ginn::BaseNode::dev](api/Classes/classginn_1_1_base_node.md#function-dev)


### function shape

```cpp
inline virtual Shape shape() const override
```


**Reimplements**: [ginn::BaseNode::shape](api/Classes/classginn_1_1_base_node.md#function-shape)


**Reimplemented by**: [ginn::DataNode::shape](api/Classes/classginn_1_1_data_node.md#function-shape), [ginn::WeightNode::shape](api/Classes/classginn_1_1_weight_node.md#function-shape)


### function init_grad

```cpp
inline virtual void init_grad() override
```


**Reimplements**: [ginn::BaseNode::init_grad](api/Classes/classginn_1_1_base_node.md#function-init_grad)


### function reset_grad

```cpp
inline virtual void reset_grad() override
```


**Reimplements**: [ginn::BaseNode::reset_grad](api/Classes/classginn_1_1_base_node.md#function-reset_grad)


### function item

```cpp
inline Scalar item() const
```


### function BaseNode

```cpp
BaseNode() =default
```


### function BaseNode

```cpp
inline BaseNode(
    const std::vector< BaseNodePtr > & ins
)
```


### function BaseNode

```cpp
template <typename Container >
inline BaseNode(
    const Container & ins
)
```


-------------------------------

Updated on 2022-12-24 at 15:34:35 -0500
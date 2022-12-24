# ginn::ContainerwiseLayerNode< Container, InnerOut(InnerIn)>


 [More...](#detailed-description)

Inherits from [ginn::CombinedLayerNode< Container< InnerOut >(Container< InnerIn >)>](api/Classes/classginn_1_1_combined_layer_node.md), [ginn::LayerNode< Func >](api/Classes/classginn_1_1_layer_node.md)

## Public Types

|                | Name           |
| -------------- | -------------- |
| using Container< InnerIn > | **[InputType](api/Classes/classginn_1_1_containerwise_layer_node_3_01_container_00_01_inner_out_07_inner_in_08_4.md#using-inputtype)**  |
| using Container< InnerOut > | **[OutputType](api/Classes/classginn_1_1_containerwise_layer_node_3_01_container_00_01_inner_out_07_inner_in_08_4.md#using-outputtype)**  |
| using InnerIn | **[InputValueType](api/Classes/classginn_1_1_containerwise_layer_node_3_01_container_00_01_inner_out_07_inner_in_08_4.md#using-inputvaluetype)**  |
| using InnerOut | **[OutputValueType](api/Classes/classginn_1_1_containerwise_layer_node_3_01_container_00_01_inner_out_07_inner_in_08_4.md#using-outputvaluetype)**  |

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[ContainerwiseLayerNode](api/Classes/classginn_1_1_containerwise_layer_node_3_01_container_00_01_inner_out_07_inner_in_08_4.md#function-containerwiselayernode)**(LayerPtr< InnerOut(InnerIn)> inner) |
| virtual std::vector< ConstLayerBasePtr > | **[children](api/Classes/classginn_1_1_containerwise_layer_node_3_01_container_00_01_inner_out_07_inner_in_08_4.md#function-children)**() const override |
| OutputType | **[run](api/Classes/classginn_1_1_containerwise_layer_node_3_01_container_00_01_inner_out_07_inner_in_08_4.md#function-run)**(const InputType & x) override |
| LayerPtr< OutputType(InputType)> | **[copy](api/Classes/classginn_1_1_containerwise_layer_node_3_01_container_00_01_inner_out_07_inner_in_08_4.md#function-copy)**(Copy mode) override |

## Additional inherited members

**Public Functions inherited from [ginn::CombinedLayerNode< Container< InnerOut >(Container< InnerIn >)>](api/Classes/classginn_1_1_combined_layer_node.md)**

|                | Name           |
| -------------- | -------------- |
| std::vector< [BaseNodePtr](api/Classes/classginn_1_1_ptr.md) > | **[weights_](api/Classes/classginn_1_1_combined_layer_node.md#function-weights_)**() override |
| void | **[set_mode](api/Classes/classginn_1_1_combined_layer_node.md#function-set_mode)**(Mode mode) override |
| Mode | **[mode](api/Classes/classginn_1_1_combined_layer_node.md#function-mode)**() const override |


## Detailed Description

```cpp
template <template< typename... > class Container,
typename InnerOut ,
typename InnerIn >
class ginn::ContainerwiseLayerNode< Container, InnerOut(InnerIn)>;
```

## Public Types Documentation

### using InputType

```cpp
using ginn::ContainerwiseLayerNode< Container, InnerOut(InnerIn)>::InputType =  Container<InnerIn>;
```


### using OutputType

```cpp
using ginn::ContainerwiseLayerNode< Container, InnerOut(InnerIn)>::OutputType =  Container<InnerOut>;
```


### using InputValueType

```cpp
using ginn::ContainerwiseLayerNode< Container, InnerOut(InnerIn)>::InputValueType =  InnerIn;
```


### using OutputValueType

```cpp
using ginn::ContainerwiseLayerNode< Container, InnerOut(InnerIn)>::OutputValueType =  InnerOut;
```


## Public Functions Documentation

### function ContainerwiseLayerNode

```cpp
inline ContainerwiseLayerNode(
    LayerPtr< InnerOut(InnerIn)> inner
)
```


### function children

```cpp
inline virtual std::vector< ConstLayerBasePtr > children() const override
```


**Reimplements**: [ginn::CombinedLayerNode::children](api/Classes/classginn_1_1_combined_layer_node.md#function-children)


### function run

```cpp
inline OutputType run(
    const InputType & x
) override
```


### function copy

```cpp
inline LayerPtr< OutputType(InputType)> copy(
    Copy mode
) override
```


-------------------------------

Updated on 2022-12-24 at 14:52:49 -0500
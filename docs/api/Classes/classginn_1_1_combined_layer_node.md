# ginn::CombinedLayerNode


 [More...](#detailed-description)

Inherits from [ginn::LayerNode< Func >](api/Classes/classginn_1_1_layer_node.md)

## Public Functions

|                | Name           |
| -------------- | -------------- |
| virtual std::vector< ConstLayerBasePtr > | **[children](api/Classes/classginn_1_1_combined_layer_node.md#function-children)**() const =0 |
| std::vector< LayerBasePtr > | **[children](api/Classes/classginn_1_1_combined_layer_node.md#function-children)**() |
| std::vector< [BaseNodePtr](api/Classes/classginn_1_1_ptr.md) > | **[weights_](api/Classes/classginn_1_1_combined_layer_node.md#function-weights_)**() override |
| void | **[set_mode](api/Classes/classginn_1_1_combined_layer_node.md#function-set_mode)**(Mode mode) override |
| Mode | **[mode](api/Classes/classginn_1_1_combined_layer_node.md#function-mode)**() const override |

## Detailed Description

```cpp
template <typename Func >
class ginn::CombinedLayerNode;
```

## Public Functions Documentation

### function children

```cpp
virtual std::vector< ConstLayerBasePtr > children() const =0
```


**Reimplemented by**: [ginn::ContainerwiseLayerNode< Container, InnerOut(InnerIn)>::children](api/Classes/classginn_1_1_containerwise_layer_node_3_01_container_00_01_inner_out_07_inner_in_08_4.md#function-children), [ginn::JoinLayerNode< std::tuple< Out, Out2 >(std::tuple< In, In2 >)>::children](api/Classes/classginn_1_1_join_layer_node_3_01std_1_1tuple_3_01_out_00_01_out2_01_4_07std_1_1tuple_3_01_in_00_01_in2_01_4_08_4.md#function-children), [ginn::StackedLayerNode< Out(In)>::children](api/Classes/classginn_1_1_stacked_layer_node_3_01_out_07_in_08_4.md#function-children)


### function children

```cpp
inline std::vector< LayerBasePtr > children()
```


### function weights_

```cpp
inline std::vector< BaseNodePtr > weights_() override
```


### function set_mode

```cpp
inline void set_mode(
    Mode mode
) override
```


### function mode

```cpp
inline Mode mode() const override
```


-------------------------------

Updated on 2022-12-24 at 14:52:49 -0500
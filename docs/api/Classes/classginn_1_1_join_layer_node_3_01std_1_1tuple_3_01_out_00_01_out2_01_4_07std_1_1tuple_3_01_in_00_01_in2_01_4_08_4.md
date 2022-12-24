# ginn::JoinLayerNode< std::tuple< Out, Out2 >(std::tuple< In, In2 >)>


 [More...](#detailed-description)

Inherits from [ginn::CombinedLayerNode< std::tuple< Out, Out2 >(std::tuple< In, In2 >)>](api/Classes/classginn_1_1_combined_layer_node.md), [ginn::LayerNode< Func >](api/Classes/classginn_1_1_layer_node.md)

## Public Types

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| using std::tuple< In, In2 > | **[InputType](api/Classes/classginn_1_1_join_layer_node_3_01std_1_1tuple_3_01_out_00_01_out2_01_4_07std_1_1tuple_3_01_in_00_01_in2_01_4_08_4.md#using-inputtype)**  |
| using std::tuple< Out, Out2 > | **[OutputType](api/Classes/classginn_1_1_join_layer_node_3_01std_1_1tuple_3_01_out_00_01_out2_01_4_07std_1_1tuple_3_01_in_00_01_in2_01_4_08_4.md#using-outputtype)**  |


</span>

## Public Functions

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| | **[JoinLayerNode](api/Classes/classginn_1_1_join_layer_node_3_01std_1_1tuple_3_01_out_00_01_out2_01_4_07std_1_1tuple_3_01_in_00_01_in2_01_4_08_4.md#function-joinlayernode)**(LayerPtr< Out(In)> left, LayerPtr< Out2(In2)> right) |
| virtual std::vector< ConstLayerBasePtr > | **[children](api/Classes/classginn_1_1_join_layer_node_3_01std_1_1tuple_3_01_out_00_01_out2_01_4_07std_1_1tuple_3_01_in_00_01_in2_01_4_08_4.md#function-children)**() const override |
| OutputType | **[run](api/Classes/classginn_1_1_join_layer_node_3_01std_1_1tuple_3_01_out_00_01_out2_01_4_07std_1_1tuple_3_01_in_00_01_in2_01_4_08_4.md#function-run)**(const InputType & xs) override |
| LayerPtr< OutputType(InputType)> | **[copy](api/Classes/classginn_1_1_join_layer_node_3_01std_1_1tuple_3_01_out_00_01_out2_01_4_07std_1_1tuple_3_01_in_00_01_in2_01_4_08_4.md#function-copy)**(Copy mode) override |


</span>

## Additional inherited members

</span>

**Public Functions inherited from [ginn::CombinedLayerNode< std::tuple< Out, Out2 >(std::tuple< In, In2 >)>](api/Classes/classginn_1_1_combined_layer_node.md)**

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| std::vector< [BaseNodePtr](api/Classes/classginn_1_1_ptr.md) > | **[weights_](api/Classes/classginn_1_1_combined_layer_node.md#function-weights_)**() override |
| void | **[set_mode](api/Classes/classginn_1_1_combined_layer_node.md#function-set_mode)**(Mode mode) override |
| Mode | **[mode](api/Classes/classginn_1_1_combined_layer_node.md#function-mode)**() const override |


</span>

</span>


## Detailed Description

```cpp
template <typename Out ,
typename In ,
typename Out2 ,
typename In2 >
class ginn::JoinLayerNode< std::tuple< Out, Out2 >(std::tuple< In, In2 >)>;
```

## Public Types Documentation

### using InputType

```cpp
using ginn::JoinLayerNode< std::tuple< Out, Out2 >(std::tuple< In, In2 >)>::InputType =  std::tuple<In, In2>;
```


### using OutputType

```cpp
using ginn::JoinLayerNode< std::tuple< Out, Out2 >(std::tuple< In, In2 >)>::OutputType =  std::tuple<Out, Out2>;
```


## Public Functions Documentation

### function JoinLayerNode

```cpp
inline JoinLayerNode(
    LayerPtr< Out(In)> left,
    LayerPtr< Out2(In2)> right
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
    const InputType & xs
) override
```


### function copy

```cpp
inline LayerPtr< OutputType(InputType)> copy(
    Copy mode
) override
```


-------------------------------

Updated on 2022-12-24 at 15:34:35 -0500
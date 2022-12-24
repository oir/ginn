# ginn::StackedLayerNode< Out(In)>


 [More...](#detailed-description)

Inherits from [ginn::CombinedLayerNode< Out(In)>](api/Classes/classginn_1_1_combined_layer_node.md), [ginn::LayerNode< Func >](api/Classes/classginn_1_1_layer_node.md)

## Public Functions

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| template <typename MidIn ,typename MidOut \> <br>| **[StackedLayerNode](api/Classes/classginn_1_1_stacked_layer_node_3_01_out_07_in_08_4.md#function-stackedlayernode)**(LayerPtr< MidIn(In)> inner, LayerPtr< Out(MidOut)> outer) |
| virtual std::vector< ConstLayerBasePtr > | **[children](api/Classes/classginn_1_1_stacked_layer_node_3_01_out_07_in_08_4.md#function-children)**() const override |
| Out | **[run](api/Classes/classginn_1_1_stacked_layer_node_3_01_out_07_in_08_4.md#function-run)**(const In & x) override |
| LayerPtr< Out(In)> | **[copy](api/Classes/classginn_1_1_stacked_layer_node_3_01_out_07_in_08_4.md#function-copy)**(Copy mode =Copy::Tied) override |


</span>

## Additional inherited members

</span>

**Public Functions inherited from [ginn::CombinedLayerNode< Out(In)>](api/Classes/classginn_1_1_combined_layer_node.md)**

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
typename In >
class ginn::StackedLayerNode< Out(In)>;
```

## Public Functions Documentation

### function StackedLayerNode

```cpp
template <typename MidIn ,
typename MidOut >
inline StackedLayerNode(
    LayerPtr< MidIn(In)> inner,
    LayerPtr< Out(MidOut)> outer
)
```


### function children

```cpp
inline virtual std::vector< ConstLayerBasePtr > children() const override
```


**Reimplements**: [ginn::CombinedLayerNode::children](api/Classes/classginn_1_1_combined_layer_node.md#function-children)


### function run

```cpp
inline Out run(
    const In & x
) override
```


### function copy

```cpp
inline LayerPtr< Out(In)> copy(
    Copy mode =Copy::Tied
) override
```


-------------------------------

Updated on 2022-12-24 at 15:34:35 -0500
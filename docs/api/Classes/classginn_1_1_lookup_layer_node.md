# ginn::LookupLayerNode


 [More...](#detailed-description)

Inherits from [ginn::LayerNode< Func >](api/Classes/classginn_1_1_layer_node.md)

## Public Types

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| using typename [FunctionTraits](api/Classes/structginn_1_1_function_traits.md)< Func >::arg_t | **[InputType](api/Classes/classginn_1_1_lookup_layer_node.md#using-inputtype)**  |
| using typename [FunctionTraits](api/Classes/structginn_1_1_function_traits.md)< Func >::result_t | **[OutputType](api/Classes/classginn_1_1_lookup_layer_node.md#using-outputtype)**  |
| using std::unordered_set< InputType > | **[Set](api/Classes/classginn_1_1_lookup_layer_node.md#using-set)**  |


</span>

## Public Functions

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| | **[LookupLayerNode](api/Classes/classginn_1_1_lookup_layer_node.md#function-lookuplayernode)**() =default |
| | **[LookupLayerNode](api/Classes/classginn_1_1_lookup_layer_node.md#function-lookuplayernode)**(DevPtr dev, Size dim, Real drop_p =0., const Set & vocab ={}) |
| LayerPtr< Func > | **[copy](api/Classes/classginn_1_1_lookup_layer_node.md#function-copy)**(Copy mode) override |
| OutputType | **[run](api/Classes/classginn_1_1_lookup_layer_node.md#function-run)**(const InputType & x) override |
| std::vector< [BaseNodePtr](api/Classes/classginn_1_1_ptr.md) > | **[weights_](api/Classes/classginn_1_1_lookup_layer_node.md#function-weights_)**() override |


</span>

## Public Attributes

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| [LookupTable](api/Classes/classginn_1_1_lookup_table.md)< InputType, OutputType > | **[table](api/Classes/classginn_1_1_lookup_layer_node.md#variable-table)**  |


</span>

## Detailed Description

```cpp
template <typename Func >
class ginn::LookupLayerNode;
```

## Public Types Documentation

### using InputType

```cpp
using ginn::LookupLayerNode< Func >::InputType =  typename FunctionTraits<Func>::arg_t;
```


### using OutputType

```cpp
using ginn::LookupLayerNode< Func >::OutputType =  typename FunctionTraits<Func>::result_t;
```


### using Set

```cpp
using ginn::LookupLayerNode< Func >::Set =  std::unordered_set<InputType>;
```


## Public Functions Documentation

### function LookupLayerNode

```cpp
LookupLayerNode() =default
```


### function LookupLayerNode

```cpp
inline LookupLayerNode(
    DevPtr dev,
    Size dim,
    Real drop_p =0.,
    const Set & vocab ={}
)
```


### function copy

```cpp
inline LayerPtr< Func > copy(
    Copy mode
) override
```


### function run

```cpp
inline OutputType run(
    const InputType & x
) override
```


### function weights_

```cpp
inline std::vector< BaseNodePtr > weights_() override
```


## Public Attributes Documentation

### variable table

```cpp
LookupTable< InputType, OutputType > table;
```


-------------------------------

Updated on 2022-12-24 at 15:34:35 -0500
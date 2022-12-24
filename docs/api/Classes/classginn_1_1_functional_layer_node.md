# ginn::FunctionalLayerNode


 [More...](#detailed-description)

Inherits from [ginn::LayerNode< Func >](api/Classes/classginn_1_1_layer_node.md)

## Public Types

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| using typename [FunctionTraits](api/Classes/structginn_1_1_function_traits.md)< Func >::arg_t | **[InputType](api/Classes/classginn_1_1_functional_layer_node.md#using-inputtype)**  |
| using typename [FunctionTraits](api/Classes/structginn_1_1_function_traits.md)< Func >::result_t | **[OutputType](api/Classes/classginn_1_1_functional_layer_node.md#using-outputtype)**  |


</span>

## Public Functions

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| | **[FunctionalLayerNode](api/Classes/classginn_1_1_functional_layer_node.md#function-functionallayernode)**(std::function< OutputType(const InputType &)> f) |
| OutputType | **[run](api/Classes/classginn_1_1_functional_layer_node.md#function-run)**(const InputType & x) override |
| LayerPtr< Func > | **[copy](api/Classes/classginn_1_1_functional_layer_node.md#function-copy)**(Copy ) override |


</span>

## Detailed Description

```cpp
template <typename Func >
class ginn::FunctionalLayerNode;
```

## Public Types Documentation

### using InputType

```cpp
using ginn::FunctionalLayerNode< Func >::InputType =  typename FunctionTraits<Func>::arg_t;
```


### using OutputType

```cpp
using ginn::FunctionalLayerNode< Func >::OutputType =  typename FunctionTraits<Func>::result_t;
```


## Public Functions Documentation

### function FunctionalLayerNode

```cpp
inline FunctionalLayerNode(
    std::function< OutputType(const InputType &)> f
)
```


### function run

```cpp
inline OutputType run(
    const InputType & x
) override
```


### function copy

```cpp
inline LayerPtr< Func > copy(
    Copy 
) override
```


-------------------------------

Updated on 2022-12-24 at 15:34:35 -0500
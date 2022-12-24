# ginn::LayerNode< Out(In)>


 [More...](#detailed-description)

Inherits from [ginn::LayerNodeBase](api/Classes/classginn_1_1_layer_node_base.md)

## Public Types

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| using Out(In) | **[function_t](api/Classes/classginn_1_1_layer_node_3_01_out_07_in_08_4.md#using-function_t)**  |
| using In | **[arg_t](api/Classes/classginn_1_1_layer_node_3_01_out_07_in_08_4.md#using-arg_t)**  |
| using Out | **[result_t](api/Classes/classginn_1_1_layer_node_3_01_out_07_in_08_4.md#using-result_t)**  |


</span>

## Public Functions

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| virtual Out | **[run](api/Classes/classginn_1_1_layer_node_3_01_out_07_in_08_4.md#function-run)**(const In & ) =0 |
| virtual LayerPtr< Out(In)> | **[copy](api/Classes/classginn_1_1_layer_node_3_01_out_07_in_08_4.md#function-copy)**(Copy mode) =0 |


</span>

## Additional inherited members

</span>

**Public Functions inherited from [ginn::LayerNodeBase](api/Classes/classginn_1_1_layer_node_base.md)**

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| virtual std::vector< [BaseNodePtr](api/Classes/classginn_1_1_ptr.md) > | **[weights_](api/Classes/classginn_1_1_layer_node_base.md#function-weights_)**() |
| template <typename Scalar \> <br>std::vector< [WeightPtr](api/Classes/classginn_1_1_ptr.md)< Scalar > > | **[weights](api/Classes/classginn_1_1_layer_node_base.md#function-weights)**() |
| virtual void | **[set_mode](api/Classes/classginn_1_1_layer_node_base.md#function-set_mode)**(Mode mode) |
| virtual Mode | **[mode](api/Classes/classginn_1_1_layer_node_base.md#function-mode)**() const |
| virtual | **[~LayerNodeBase](api/Classes/classginn_1_1_layer_node_base.md#function-~layernodebase)**() =default |


</span>


## Detailed Description

```cpp
template <typename Out ,
typename In >
class ginn::LayerNode< Out(In)>;
```

## Public Types Documentation

### using function_t

```cpp
using ginn::LayerNode< Out(In)>::function_t =  Out(In);
```


### using arg_t

```cpp
using ginn::LayerNode< Out(In)>::arg_t =  In;
```


### using result_t

```cpp
using ginn::LayerNode< Out(In)>::result_t =  Out;
```


## Public Functions Documentation

### function run

```cpp
virtual Out run(
    const In & 
) =0
```


### function copy

```cpp
virtual LayerPtr< Out(In)> copy(
    Copy mode
) =0
```


-------------------------------

Updated on 2022-12-24 at 15:34:35 -0500
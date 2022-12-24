# ginn::InPlaceLayerNormNode


 [More...](#detailed-description)

Inherits from [ginn::LayerNormNode< Scalar >](api/Classes/classginn_1_1_layer_norm_node.md), [ginn::BaseDataNode< Scalar >](api/Classes/classginn_1_1_base_data_node.md), [ginn::Node< Real >](api/Classes/classginn_1_1_node.md), [ginn::BaseNode](api/Classes/classginn_1_1_base_node.md)

## Public Functions

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| virtual const [Tensor](api/Classes/classginn_1_1_tensor.md)< Scalar > & | **[value](api/Classes/classginn_1_1_in_place_layer_norm_node.md#function-value)**() const override |
| virtual const [Tensor](api/Classes/classginn_1_1_tensor.md)< Scalar > & | **[grad](api/Classes/classginn_1_1_in_place_layer_norm_node.md#function-grad)**() const override |
| virtual bool | **[has_grad](api/Classes/classginn_1_1_in_place_layer_norm_node.md#function-has_grad)**() const override |
| virtual std::string | **[name](api/Classes/classginn_1_1_in_place_layer_norm_node.md#function-name)**() const override |


</span>

## Protected Functions

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| virtual void | **[backward_](api/Classes/classginn_1_1_in_place_layer_norm_node.md#function-backward_)**() override |


</span>

## Additional inherited members

</span>

**Public Functions inherited from [ginn::LayerNormNode< Scalar >](api/Classes/classginn_1_1_layer_norm_node.md)**

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| | **[LayerNormNode](api/Classes/classginn_1_1_layer_norm_node.md#function-layernormnode)**([NodePtr](api/Classes/classginn_1_1_ptr.md)< Scalar > in, Scalar eps =Scalar(1e-8)) |


</span>

**Protected Functions inherited from [ginn::LayerNormNode< Scalar >](api/Classes/classginn_1_1_layer_norm_node.md)**

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| virtual void | **[forward_](api/Classes/classginn_1_1_layer_norm_node.md#function-forward_)**() override |


</span>

**Protected Attributes inherited from [ginn::LayerNormNode< Scalar >](api/Classes/classginn_1_1_layer_norm_node.md)**

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| [NodePtr](api/Classes/classginn_1_1_ptr.md)< Scalar > | **[in_](api/Classes/classginn_1_1_layer_norm_node.md#variable-in_)**  |
| Scalar | **[eps_](api/Classes/classginn_1_1_layer_norm_node.md#variable-eps_)**  |
| [Tensor](api/Classes/classginn_1_1_tensor.md)< Scalar > | **[mean_](api/Classes/classginn_1_1_layer_norm_node.md#variable-mean_)**  |
| [Tensor](api/Classes/classginn_1_1_tensor.md)< Scalar > | **[std_](api/Classes/classginn_1_1_layer_norm_node.md#variable-std_)**  |


</span>

</span>

**Public Functions inherited from [ginn::BaseDataNode< Scalar >](api/Classes/classginn_1_1_base_data_node.md)**

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| | **[BaseDataNode](api/Classes/classginn_1_1_base_data_node.md#function-basedatanode)**(DevPtr dev, const std::vector< [BaseNodePtr](api/Classes/classginn_1_1_ptr.md) > & ins) |
| | **[BaseDataNode](api/Classes/classginn_1_1_base_data_node.md#function-basedatanode)**(DevPtr dev, const Shape & shape, const std::vector< [BaseNodePtr](api/Classes/classginn_1_1_ptr.md) > & ins) |
| template <typename NodeType \> <br>| **[BaseDataNode](api/Classes/classginn_1_1_base_data_node.md#function-basedatanode)**(const std::vector< NodeType > & ins) |
| | **[BaseDataNode](api/Classes/classginn_1_1_base_data_node.md#function-basedatanode)**(DevPtr dev =cpu()) |
| | **[BaseDataNode](api/Classes/classginn_1_1_base_data_node.md#function-basedatanode)**(const Shape & shape) |
| | **[BaseDataNode](api/Classes/classginn_1_1_base_data_node.md#function-basedatanode)**(DevPtr dev, const Shape & shape) |
| | **[BaseDataNode](api/Classes/classginn_1_1_base_data_node.md#function-basedatanode)**(const std::initializer_list< [BaseNodePtr](api/Classes/classginn_1_1_ptr.md) > & ins) |
| | **[BaseDataNode](api/Classes/classginn_1_1_base_data_node.md#function-basedatanode)**(DevPtr dev, const std::initializer_list< [BaseNodePtr](api/Classes/classginn_1_1_ptr.md) > & ins) |


</span>

**Public Types inherited from [ginn::Node< Real >](api/Classes/classginn_1_1_node.md)**

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| using ScalarType | **[Scalar](api/Classes/classginn_1_1_node.md#using-scalar)**  |

</span>

**Public Functions inherited from [ginn::Node< Real >](api/Classes/classginn_1_1_node.md)**

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| virtual DevPtr | **[dev](api/Classes/classginn_1_1_node.md#function-dev)**() const override |
| virtual Shape | **[shape](api/Classes/classginn_1_1_node.md#function-shape)**() const override |
| virtual void | **[init_grad](api/Classes/classginn_1_1_node.md#function-init_grad)**() override |
| virtual void | **[reset_grad](api/Classes/classginn_1_1_node.md#function-reset_grad)**() override |
| Scalar | **[item](api/Classes/classginn_1_1_node.md#function-item)**() const |
| | **[BaseNode](api/Classes/classginn_1_1_node.md#function-basenode)**() =default |
| | **[BaseNode](api/Classes/classginn_1_1_node.md#function-basenode)**(const std::vector< [BaseNodePtr](api/Classes/classginn_1_1_ptr.md) > & ins) |
| template <typename Container \> <br>| **[BaseNode](api/Classes/classginn_1_1_node.md#function-basenode)**(const Container & ins) |


</span>

</span>

**Public Functions inherited from [ginn::BaseNode](api/Classes/classginn_1_1_base_node.md)**

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| | **[BaseNode](api/Classes/classginn_1_1_base_node.md#function-basenode)**() =default |
| const auto & | **[ins](api/Classes/classginn_1_1_base_node.md#function-ins)**() |
| std::vector< [ConstBaseNodePtr](api/Classes/classginn_1_1_ptr.md) > | **[ins](api/Classes/classginn_1_1_base_node.md#function-ins)**() const |
| const [BaseNodePtr](api/Classes/classginn_1_1_ptr.md) & | **[in](api/Classes/classginn_1_1_base_node.md#function-in)**(size_t idx =0) |
| [ConstBaseNodePtr](api/Classes/classginn_1_1_ptr.md) | **[in](api/Classes/classginn_1_1_base_node.md#function-in)**(size_t idx =0) const |
| virtual void | **[set_ins](api/Classes/classginn_1_1_base_node.md#function-set_ins)**(const std::vector< [BaseNodePtr](api/Classes/classginn_1_1_ptr.md) > & ) |
| | **[BaseNode](api/Classes/classginn_1_1_base_node.md#function-basenode)**(const std::vector< [BaseNodePtr](api/Classes/classginn_1_1_ptr.md) > & ins) |
| template <typename Container \> <br>| **[BaseNode](api/Classes/classginn_1_1_base_node.md#function-basenode)**(const Container & ins) |
| virtual | **[~BaseNode](api/Classes/classginn_1_1_base_node.md#function-~basenode)**() =default |
| virtual DevPtr | **[dev](api/Classes/classginn_1_1_base_node.md#function-dev)**() const =0 |
| virtual Shape | **[shape](api/Classes/classginn_1_1_base_node.md#function-shape)**() const =0 |
| Shape | **[shape2](api/Classes/classginn_1_1_base_node.md#function-shape2)**() const |
| Size | **[rows](api/Classes/classginn_1_1_base_node.md#function-rows)**() const |
| Size | **[cols](api/Classes/classginn_1_1_base_node.md#function-cols)**() const |
| Size | **[size](api/Classes/classginn_1_1_base_node.md#function-size)**() const |
| void | **[forward](api/Classes/classginn_1_1_base_node.md#function-forward)**() |
| void | **[backward](api/Classes/classginn_1_1_base_node.md#function-backward)**() |
| virtual void | **[init_grad](api/Classes/classginn_1_1_base_node.md#function-init_grad)**() |
| virtual void | **[reset_grad](api/Classes/classginn_1_1_base_node.md#function-reset_grad)**() |
| virtual void | **[reset_forwarded](api/Classes/classginn_1_1_base_node.md#function-reset_forwarded)**() |


</span>

**Protected Functions inherited from [ginn::BaseNode](api/Classes/classginn_1_1_base_node.md)**

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| virtual void | **[forward_](api/Classes/classginn_1_1_base_node.md#function-forward_)**() |


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
template <typename Scalar >
class ginn::InPlaceLayerNormNode;
```

## Public Functions Documentation

### function value

```cpp
inline virtual const Tensor< Scalar > & value() const override
```


**Reimplements**: [ginn::Node::value](api/Classes/classginn_1_1_node.md#function-value)


### function grad

```cpp
inline virtual const Tensor< Scalar > & grad() const override
```


**Reimplements**: [ginn::Node::grad](api/Classes/classginn_1_1_node.md#function-grad)


### function has_grad

```cpp
inline virtual bool has_grad() const override
```


**Reimplements**: [ginn::BaseNode::has_grad](api/Classes/classginn_1_1_base_node.md#function-has_grad)


### function name

```cpp
inline virtual std::string name() const override
```


**Reimplements**: [ginn::BaseDataNode::name](api/Classes/classginn_1_1_base_data_node.md#function-name)


## Protected Functions Documentation

### function backward_

```cpp
inline virtual void backward_() override
```


**Reimplements**: [ginn::BaseNode::backward_](api/Classes/classginn_1_1_base_node.md#function-backward_)


-------------------------------

Updated on 2022-12-24 at 15:34:35 -0500
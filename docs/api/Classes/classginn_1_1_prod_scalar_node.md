# ginn::ProdScalarNode


 [More...](#detailed-description)

Inherits from [ginn::BaseDataNode< Scalar >](api/Classes/classginn_1_1_base_data_node.md), [ginn::Node< Real >](api/Classes/classginn_1_1_node.md), [ginn::BaseNode](api/Classes/classginn_1_1_base_node.md)

Inherited by [ginn::InPlaceProdScalarNode< Scalar >](api/Classes/classginn_1_1_in_place_prod_scalar_node.md)

## Public Functions

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| template <typename RightScalar ,typename  =std::enable_if_t<ginn::is_arithmetic_v<RightScalar>>\> <br>| **[ProdScalarNode](api/Classes/classginn_1_1_prod_scalar_node.md#function-prodscalarnode)**(const [NodePtr](api/Classes/classginn_1_1_ptr.md)< Scalar > & a, RightScalar b) |
| virtual std::string | **[name](api/Classes/classginn_1_1_prod_scalar_node.md#function-name)**() const override |


</span>

## Protected Functions

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| virtual void | **[forward_](api/Classes/classginn_1_1_prod_scalar_node.md#function-forward_)**() override |
| virtual void | **[backward_](api/Classes/classginn_1_1_prod_scalar_node.md#function-backward_)**() override |


</span>

## Protected Attributes

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| [NodePtr](api/Classes/classginn_1_1_ptr.md)< Scalar > | **[in_](api/Classes/classginn_1_1_prod_scalar_node.md#variable-in_)**  |
| Scalar | **[val_](api/Classes/classginn_1_1_prod_scalar_node.md#variable-val_)**  |


</span>

## Additional inherited members

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
| virtual const [Tensor](api/Classes/classginn_1_1_tensor.md)< Scalar > & | **[value](api/Classes/classginn_1_1_base_data_node.md#function-value)**() const override |
| virtual const [Tensor](api/Classes/classginn_1_1_tensor.md)< Scalar > & | **[grad](api/Classes/classginn_1_1_base_data_node.md#function-grad)**() const override |
| virtual bool | **[has_grad](api/Classes/classginn_1_1_base_data_node.md#function-has_grad)**() const override |
| virtual void | **[has_grad](api/Classes/classginn_1_1_base_data_node.md#function-has_grad)**(bool hg) |


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
| virtual bool | **[has_grad](api/Classes/classginn_1_1_base_node.md#function-has_grad)**() const |
| virtual void | **[init_grad](api/Classes/classginn_1_1_base_node.md#function-init_grad)**() |
| virtual void | **[reset_grad](api/Classes/classginn_1_1_base_node.md#function-reset_grad)**() |
| virtual void | **[reset_forwarded](api/Classes/classginn_1_1_base_node.md#function-reset_forwarded)**() |


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
class ginn::ProdScalarNode;
```

## Public Functions Documentation

### function ProdScalarNode

```cpp
template <typename RightScalar ,
typename  =std::enable_if_t<ginn::is_arithmetic_v<RightScalar>>>
inline ProdScalarNode(
    const NodePtr< Scalar > & a,
    RightScalar b
)
```


### function name

```cpp
inline virtual std::string name() const override
```


**Reimplements**: [ginn::BaseDataNode::name](api/Classes/classginn_1_1_base_data_node.md#function-name)


**Reimplemented by**: [ginn::InPlaceProdScalarNode::name](api/Classes/classginn_1_1_in_place_prod_scalar_node.md#function-name)


## Protected Functions Documentation

### function forward_

```cpp
inline virtual void forward_() override
```


**Reimplements**: [ginn::BaseNode::forward_](api/Classes/classginn_1_1_base_node.md#function-forward_)


### function backward_

```cpp
inline virtual void backward_() override
```


**Reimplements**: [ginn::BaseNode::backward_](api/Classes/classginn_1_1_base_node.md#function-backward_)


**Reimplemented by**: [ginn::InPlaceProdScalarNode::backward_](api/Classes/classginn_1_1_in_place_prod_scalar_node.md#function-backward_)


## Protected Attributes Documentation

### variable in_

```cpp
NodePtr< Scalar > in_;
```


### variable val_

```cpp
Scalar val_;
```


-------------------------------

Updated on 2022-12-24 at 15:34:35 -0500
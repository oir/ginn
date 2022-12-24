# ginn::DataNode


 [More...](#detailed-description)

Inherits from [ginn::BaseDataNode< Real >](api/Classes/classginn_1_1_base_data_node.md), [ginn::Node< Real >](api/Classes/classginn_1_1_node.md), [ginn::BaseNode](api/Classes/classginn_1_1_base_node.md)

## Public Functions

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| | **[DataNode](api/Classes/classginn_1_1_data_node.md#function-datanode)**(DevPtr dev =cpu()) |
| | **[DataNode](api/Classes/classginn_1_1_data_node.md#function-datanode)**(Shape shape) |
| | **[DataNode](api/Classes/classginn_1_1_data_node.md#function-datanode)**(DevPtr dev, Shape shape) |
| void | **[move_to](api/Classes/classginn_1_1_data_node.md#function-move_to)**(const DevPtr & to) |
| void | **[fill](api/Classes/classginn_1_1_data_node.md#function-fill)**(Scalar val) |
| void | **[set_zero](api/Classes/classginn_1_1_data_node.md#function-set_zero)**() |
| void | **[set_ones](api/Classes/classginn_1_1_data_node.md#function-set_ones)**() |
| void | **[set_random](api/Classes/classginn_1_1_data_node.md#function-set_random)**() |
| virtual void | **[reset_forwarded](api/Classes/classginn_1_1_data_node.md#function-reset_forwarded)**() override |
| template <typename OtherScalar \> <br>auto | **[cast](api/Classes/classginn_1_1_data_node.md#function-cast)**() const |
| virtual Shape | **[shape](api/Classes/classginn_1_1_data_node.md#function-shape)**() const override |
| virtual std::string | **[name](api/Classes/classginn_1_1_data_node.md#function-name)**() const override |


</span>

## Additional inherited members

</span>

**Public Functions inherited from [ginn::BaseDataNode< Real >](api/Classes/classginn_1_1_base_data_node.md)**

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
| Shape | **[shape2](api/Classes/classginn_1_1_base_node.md#function-shape2)**() const |
| Size | **[rows](api/Classes/classginn_1_1_base_node.md#function-rows)**() const |
| Size | **[cols](api/Classes/classginn_1_1_base_node.md#function-cols)**() const |
| Size | **[size](api/Classes/classginn_1_1_base_node.md#function-size)**() const |
| void | **[forward](api/Classes/classginn_1_1_base_node.md#function-forward)**() |
| void | **[backward](api/Classes/classginn_1_1_base_node.md#function-backward)**() |
| virtual bool | **[has_grad](api/Classes/classginn_1_1_base_node.md#function-has_grad)**() const |
| virtual void | **[init_grad](api/Classes/classginn_1_1_base_node.md#function-init_grad)**() |
| virtual void | **[reset_grad](api/Classes/classginn_1_1_base_node.md#function-reset_grad)**() |


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
template <typename Scalar  =Real>
class ginn::DataNode;
```

## Public Functions Documentation

### function DataNode

```cpp
inline DataNode(
    DevPtr dev =cpu()
)
```


### function DataNode

```cpp
inline DataNode(
    Shape shape
)
```


### function DataNode

```cpp
inline DataNode(
    DevPtr dev,
    Shape shape
)
```


### function move_to

```cpp
inline void move_to(
    const DevPtr & to
)
```


### function fill

```cpp
inline void fill(
    Scalar val
)
```


### function set_zero

```cpp
inline void set_zero()
```


### function set_ones

```cpp
inline void set_ones()
```


### function set_random

```cpp
inline void set_random()
```


### function reset_forwarded

```cpp
inline virtual void reset_forwarded() override
```


**Reimplements**: [ginn::BaseNode::reset_forwarded](api/Classes/classginn_1_1_base_node.md#function-reset_forwarded)


### function cast

```cpp
template <typename OtherScalar >
inline auto cast() const
```


### function shape

```cpp
inline virtual Shape shape() const override
```


**Reimplements**: [ginn::Node::shape](api/Classes/classginn_1_1_node.md#function-shape)


### function name

```cpp
inline virtual std::string name() const override
```


**Reimplements**: [ginn::BaseDataNode::name](api/Classes/classginn_1_1_base_data_node.md#function-name)


-------------------------------

Updated on 2022-12-24 at 15:34:35 -0500
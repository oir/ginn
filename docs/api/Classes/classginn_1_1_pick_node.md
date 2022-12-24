# ginn::PickNode


 [More...](#detailed-description)

Inherits from [ginn::BaseDataNode< Scalar >](api/Classes/classginn_1_1_base_data_node.md), [ginn::Node< Real >](api/Classes/classginn_1_1_node.md), [ginn::BaseNode](api/Classes/classginn_1_1_base_node.md)

Inherited by [ginn::PickSoftmaxNode< Scalar >](api/Classes/classginn_1_1_pick_softmax_node.md)

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[PickNode](api/Classes/classginn_1_1_pick_node.md#function-picknode)**(const [NodePtr](api/Classes/classginn_1_1_ptr.md)< Scalar > & in, const [DataPtr](api/Classes/classginn_1_1_ptr.md)< Int > & index) |
| | **[PickNode](api/Classes/classginn_1_1_pick_node.md#function-picknode)**(const [NodePtr](api/Classes/classginn_1_1_ptr.md)< Scalar > & in, const std::vector< Int > & index) |
| | **[PickNode](api/Classes/classginn_1_1_pick_node.md#function-picknode)**(const [NodePtr](api/Classes/classginn_1_1_ptr.md)< Scalar > & in, Int index) |
| virtual std::string | **[name](api/Classes/classginn_1_1_pick_node.md#function-name)**() const override |

## Protected Functions

|                | Name           |
| -------------- | -------------- |
| void | **[pick](api/Classes/classginn_1_1_pick_node.md#function-pick)**([Tensor](api/Classes/classginn_1_1_tensor.md)< Scalar > & input) |
| void | **[pick_grad](api/Classes/classginn_1_1_pick_node.md#function-pick_grad)**([Tensor](api/Classes/classginn_1_1_tensor.md)< Scalar > & grad_in, bool negate =false) |
| void | **[check_range](api/Classes/classginn_1_1_pick_node.md#function-check_range)**() |
| virtual void | **[forward_](api/Classes/classginn_1_1_pick_node.md#function-forward_)**() override |
| virtual void | **[backward_](api/Classes/classginn_1_1_pick_node.md#function-backward_)**() override |

## Protected Attributes

|                | Name           |
| -------------- | -------------- |
| [NodePtr](api/Classes/classginn_1_1_ptr.md)< Scalar > | **[in_](api/Classes/classginn_1_1_pick_node.md#variable-in_)**  |
| [DataPtr](api/Classes/classginn_1_1_ptr.md)< Int > | **[index_](api/Classes/classginn_1_1_pick_node.md#variable-index_)**  |

## Additional inherited members

**Public Functions inherited from [ginn::BaseDataNode< Scalar >](api/Classes/classginn_1_1_base_data_node.md)**

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

**Public Types inherited from [ginn::Node< Real >](api/Classes/classginn_1_1_node.md)**

|                | Name           |
| -------------- | -------------- |
| using ScalarType | **[Scalar](api/Classes/classginn_1_1_node.md#using-scalar)**  |

**Public Functions inherited from [ginn::Node< Real >](api/Classes/classginn_1_1_node.md)**

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

**Public Functions inherited from [ginn::BaseNode](api/Classes/classginn_1_1_base_node.md)**

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

**Public Attributes inherited from [ginn::BaseNode](api/Classes/classginn_1_1_base_node.md)**

|                | Name           |
| -------------- | -------------- |
| bool | **[forwarded](api/Classes/classginn_1_1_base_node.md#variable-forwarded)**  |

**Protected Attributes inherited from [ginn::BaseNode](api/Classes/classginn_1_1_base_node.md)**

|                | Name           |
| -------------- | -------------- |
| std::vector< [BaseNodePtr](api/Classes/classginn_1_1_ptr.md) > | **[ins_](api/Classes/classginn_1_1_base_node.md#variable-ins_)**  |


## Detailed Description

```cpp
template <typename Scalar >
class ginn::PickNode;
```

## Public Functions Documentation

### function PickNode

```cpp
inline PickNode(
    const NodePtr< Scalar > & in,
    const DataPtr< Int > & index
)
```


### function PickNode

```cpp
inline PickNode(
    const NodePtr< Scalar > & in,
    const std::vector< Int > & index
)
```


### function PickNode

```cpp
inline PickNode(
    const NodePtr< Scalar > & in,
    Int index
)
```


### function name

```cpp
inline virtual std::string name() const override
```


**Reimplements**: [ginn::BaseDataNode::name](api/Classes/classginn_1_1_base_data_node.md#function-name)


**Reimplemented by**: [ginn::PickSoftmaxNode::name](api/Classes/classginn_1_1_pick_softmax_node.md#function-name), [ginn::PickNegLogSoftmaxNode::name](api/Classes/classginn_1_1_pick_neg_log_softmax_node.md#function-name)


## Protected Functions Documentation

### function pick

```cpp
inline void pick(
    Tensor< Scalar > & input
)
```


### function pick_grad

```cpp
inline void pick_grad(
    Tensor< Scalar > & grad_in,
    bool negate =false
)
```


### function check_range

```cpp
inline void check_range()
```


### function forward_

```cpp
inline virtual void forward_() override
```


**Reimplements**: [ginn::BaseNode::forward_](api/Classes/classginn_1_1_base_node.md#function-forward_)


**Reimplemented by**: [ginn::PickSoftmaxNode::forward_](api/Classes/classginn_1_1_pick_softmax_node.md#function-forward_), [ginn::PickNegLogSoftmaxNode::forward_](api/Classes/classginn_1_1_pick_neg_log_softmax_node.md#function-forward_)


### function backward_

```cpp
inline virtual void backward_() override
```


**Reimplements**: [ginn::BaseNode::backward_](api/Classes/classginn_1_1_base_node.md#function-backward_)


**Reimplemented by**: [ginn::PickSoftmaxNode::backward_](api/Classes/classginn_1_1_pick_softmax_node.md#function-backward_), [ginn::PickNegLogSoftmaxNode::backward_](api/Classes/classginn_1_1_pick_neg_log_softmax_node.md#function-backward_)


## Protected Attributes Documentation

### variable in_

```cpp
NodePtr< Scalar > in_;
```


### variable index_

```cpp
DataPtr< Int > index_;
```


-------------------------------

Updated on 2022-12-24 at 14:52:49 -0500
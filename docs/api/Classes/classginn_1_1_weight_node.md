# ginn::WeightNode


 [More...](#detailed-description)

Inherits from [ginn::Node< Real >](api/Classes/classginn_1_1_node.md), [ginn::BaseNode](api/Classes/classginn_1_1_base_node.md)

## Public Functions

|                | Name           |
| -------------- | -------------- |
| [Tensor](api/Classes/classginn_1_1_tensor.md)< Scalar > & | **[value](api/Classes/classginn_1_1_weight_node.md#function-value)**() |
| virtual const [Tensor](api/Classes/classginn_1_1_tensor.md)< Scalar > & | **[value](api/Classes/classginn_1_1_weight_node.md#function-value)**() const override |
| virtual const [Tensor](api/Classes/classginn_1_1_tensor.md)< Scalar > & | **[grad](api/Classes/classginn_1_1_weight_node.md#function-grad)**() const override |
| virtual bool | **[has_grad](api/Classes/classginn_1_1_weight_node.md#function-has_grad)**() const override |
| virtual void | **[has_grad](api/Classes/classginn_1_1_weight_node.md#function-has_grad)**(bool hg) |
| size_t | **[id](api/Classes/classginn_1_1_weight_node.md#function-id)**() const |
| std::mutex & | **[access](api/Classes/classginn_1_1_weight_node.md#function-access)**() |
| | **[WeightNode](api/Classes/classginn_1_1_weight_node.md#function-weightnode)**(DevPtr dev =cpu(), const Shape & shape ={0}) |
| | **[WeightNode](api/Classes/classginn_1_1_weight_node.md#function-weightnode)**(const [WeightNode](api/Classes/classginn_1_1_weight_node.md) & other) |
| void | **[operator=](api/Classes/classginn_1_1_weight_node.md#function-operator=)**(const [WeightNode](api/Classes/classginn_1_1_weight_node.md) & other) |
| virtual void | **[reset_forwarded](api/Classes/classginn_1_1_weight_node.md#function-reset_forwarded)**() override |
| void | **[move_to](api/Classes/classginn_1_1_weight_node.md#function-move_to)**(const DevPtr & to) |
| void | **[tie](api/Classes/classginn_1_1_weight_node.md#function-tie)**(const [Ptr](api/Classes/classginn_1_1_ptr.md)< [WeightNode](api/Classes/classginn_1_1_weight_node.md) > & other) |
| auto | **[copy](api/Classes/classginn_1_1_weight_node.md#function-copy)**(Copy mode =Copy::Tied) |
| template <typename RhsScalar \> <br>void | **[fill](api/Classes/classginn_1_1_weight_node.md#function-fill)**(RhsScalar val) |
| void | **[set_zero](api/Classes/classginn_1_1_weight_node.md#function-set_zero)**() |
| void | **[set_ones](api/Classes/classginn_1_1_weight_node.md#function-set_ones)**() |
| void | **[set_random](api/Classes/classginn_1_1_weight_node.md#function-set_random)**() |
| virtual Shape | **[shape](api/Classes/classginn_1_1_weight_node.md#function-shape)**() const override |
| virtual std::string | **[name](api/Classes/classginn_1_1_weight_node.md#function-name)**() const override |

## Public Attributes

|                | Name           |
| -------------- | -------------- |
| std::string | **[label](api/Classes/classginn_1_1_weight_node.md#variable-label)**  |

## Additional inherited members

**Public Types inherited from [ginn::Node< Real >](api/Classes/classginn_1_1_node.md)**

|                | Name           |
| -------------- | -------------- |
| using ScalarType | **[Scalar](api/Classes/classginn_1_1_node.md#using-scalar)**  |

**Public Functions inherited from [ginn::Node< Real >](api/Classes/classginn_1_1_node.md)**

|                | Name           |
| -------------- | -------------- |
| virtual DevPtr | **[dev](api/Classes/classginn_1_1_node.md#function-dev)**() const override |
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
| Shape | **[shape2](api/Classes/classginn_1_1_base_node.md#function-shape2)**() const |
| Size | **[rows](api/Classes/classginn_1_1_base_node.md#function-rows)**() const |
| Size | **[cols](api/Classes/classginn_1_1_base_node.md#function-cols)**() const |
| Size | **[size](api/Classes/classginn_1_1_base_node.md#function-size)**() const |
| void | **[forward](api/Classes/classginn_1_1_base_node.md#function-forward)**() |
| void | **[backward](api/Classes/classginn_1_1_base_node.md#function-backward)**() |
| virtual void | **[init_grad](api/Classes/classginn_1_1_base_node.md#function-init_grad)**() |
| virtual void | **[reset_grad](api/Classes/classginn_1_1_base_node.md#function-reset_grad)**() |

**Protected Functions inherited from [ginn::BaseNode](api/Classes/classginn_1_1_base_node.md)**

|                | Name           |
| -------------- | -------------- |
| virtual void | **[forward_](api/Classes/classginn_1_1_base_node.md#function-forward_)**() |
| virtual void | **[backward_](api/Classes/classginn_1_1_base_node.md#function-backward_)**() |

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
template <typename Scalar  =Real>
class ginn::WeightNode;
```

## Public Functions Documentation

### function value

```cpp
inline Tensor< Scalar > & value()
```


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


### function has_grad

```cpp
inline virtual void has_grad(
    bool hg
)
```


### function id

```cpp
inline size_t id() const
```


### function access

```cpp
inline std::mutex & access()
```


### function WeightNode

```cpp
inline WeightNode(
    DevPtr dev =cpu(),
    const Shape & shape ={0}
)
```


### function WeightNode

```cpp
inline WeightNode(
    const WeightNode & other
)
```


### function operator=

```cpp
inline void operator=(
    const WeightNode & other
)
```


### function reset_forwarded

```cpp
inline virtual void reset_forwarded() override
```


**Reimplements**: [ginn::BaseNode::reset_forwarded](api/Classes/classginn_1_1_base_node.md#function-reset_forwarded)


### function move_to

```cpp
inline void move_to(
    const DevPtr & to
)
```


### function tie

```cpp
inline void tie(
    const Ptr< WeightNode > & other
)
```


### function copy

```cpp
inline auto copy(
    Copy mode =Copy::Tied
)
```


### function fill

```cpp
template <typename RhsScalar >
inline void fill(
    RhsScalar val
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


### function shape

```cpp
inline virtual Shape shape() const override
```


**Reimplements**: [ginn::Node::shape](api/Classes/classginn_1_1_node.md#function-shape)


### function name

```cpp
inline virtual std::string name() const override
```


**Reimplements**: [ginn::BaseNode::name](api/Classes/classginn_1_1_base_node.md#function-name)


## Public Attributes Documentation

### variable label

```cpp
std::string label;
```


-------------------------------

Updated on 2022-12-24 at 14:52:49 -0500
# ginn::AddNode


 [More...](#detailed-description)

Inherits from [ginn::BaseDataNode< Scalar >](api/Classes/classginn_1_1_base_data_node.md), [ginn::Node< Real >](api/Classes/classginn_1_1_node.md), [ginn::BaseNode](api/Classes/classginn_1_1_base_node.md)

Inherited by [ginn::InPlaceAddNode< Scalar >](api/Classes/classginn_1_1_in_place_add_node.md)

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[AddNode](api/Classes/classginn_1_1_add_node.md#function-addnode)**(const std::vector< [NodePtr](api/Classes/classginn_1_1_ptr.md)< Scalar > > & ins) |
| template <typename... Args\> <br>| **[AddNode](api/Classes/classginn_1_1_add_node.md#function-addnode)**(const [NodePtr](api/Classes/classginn_1_1_ptr.md)< Scalar > & in, const [Args](api/Classes/classginn_1_1_args.md) &... args) |
| virtual void | **[set_ins](api/Classes/classginn_1_1_add_node.md#function-set_ins)**(const std::vector< [BaseNodePtr](api/Classes/classginn_1_1_ptr.md) > & ins) override |
| virtual std::string | **[name](api/Classes/classginn_1_1_add_node.md#function-name)**() const override |

## Protected Functions

|                | Name           |
| -------------- | -------------- |
| template <size_t... N\> <br>auto | **[add_helper](api/Classes/classginn_1_1_add_node.md#function-add_helper)**(size_t i, std::integer_sequence< size_t, N... > ) |
| template <size_t N\> <br>auto | **[add_helper](api/Classes/classginn_1_1_add_node.md#function-add_helper)**(size_t i) |
| virtual void | **[forward_](api/Classes/classginn_1_1_add_node.md#function-forward_)**() override |
| virtual void | **[backward_](api/Classes/classginn_1_1_add_node.md#function-backward_)**() override |

## Protected Attributes

|                | Name           |
| -------------- | -------------- |
| std::vector< [NodePtr](api/Classes/classginn_1_1_ptr.md)< Scalar > > | **[ins_](api/Classes/classginn_1_1_add_node.md#variable-ins_)**  |

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


## Detailed Description

```cpp
template <typename Scalar >
class ginn::AddNode;
```

## Public Functions Documentation

### function AddNode

```cpp
inline AddNode(
    const std::vector< NodePtr< Scalar > > & ins
)
```


### function AddNode

```cpp
template <typename... Args>
inline AddNode(
    const NodePtr< Scalar > & in,
    const Args &... args
)
```


### function set_ins

```cpp
inline virtual void set_ins(
    const std::vector< BaseNodePtr > & ins
) override
```


**Reimplements**: [ginn::BaseNode::set_ins](api/Classes/classginn_1_1_base_node.md#function-set_ins)


### function name

```cpp
inline virtual std::string name() const override
```


**Reimplements**: [ginn::BaseDataNode::name](api/Classes/classginn_1_1_base_data_node.md#function-name)


**Reimplemented by**: [ginn::InPlaceAddNode::name](api/Classes/classginn_1_1_in_place_add_node.md#function-name)


## Protected Functions Documentation

### function add_helper

```cpp
template <size_t... N>
inline auto add_helper(
    size_t i,
    std::integer_sequence< size_t, N... > 
)
```


### function add_helper

```cpp
template <size_t N>
inline auto add_helper(
    size_t i
)
```


### function forward_

```cpp
inline virtual void forward_() override
```


**Reimplements**: [ginn::BaseNode::forward_](api/Classes/classginn_1_1_base_node.md#function-forward_)


**Reimplemented by**: [ginn::InPlaceAddNode::forward_](api/Classes/classginn_1_1_in_place_add_node.md#function-forward_)


### function backward_

```cpp
inline virtual void backward_() override
```


**Reimplements**: [ginn::BaseNode::backward_](api/Classes/classginn_1_1_base_node.md#function-backward_)


**Reimplemented by**: [ginn::InPlaceAddNode::backward_](api/Classes/classginn_1_1_in_place_add_node.md#function-backward_)


## Protected Attributes Documentation

### variable ins_

```cpp
std::vector< NodePtr< Scalar > > ins_;
```


-------------------------------

Updated on 2022-12-24 at 14:52:49 -0500
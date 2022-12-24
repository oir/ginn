# ginn::SinkNode




Inherits from [ginn::BaseNode](api/Classes/classginn_1_1_base_node.md)

## Public Functions

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| virtual DevPtr | **[dev](api/Classes/classginn_1_1_sink_node.md#function-dev)**() const override |
| virtual Shape | **[shape](api/Classes/classginn_1_1_sink_node.md#function-shape)**() const override |
| virtual std::string | **[name](api/Classes/classginn_1_1_sink_node.md#function-name)**() const override |
| | **[BaseNode](api/Classes/classginn_1_1_sink_node.md#function-basenode)**() =default |
| | **[BaseNode](api/Classes/classginn_1_1_sink_node.md#function-basenode)**(const std::vector< [BaseNodePtr](api/Classes/classginn_1_1_ptr.md) > & ins) |
| template <typename Container \> <br>| **[BaseNode](api/Classes/classginn_1_1_sink_node.md#function-basenode)**(const Container & ins) |


</span>

## Additional inherited members

</span>

**Public Functions inherited from [ginn::BaseNode](api/Classes/classginn_1_1_base_node.md)**

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| const auto & | **[ins](api/Classes/classginn_1_1_base_node.md#function-ins)**() |
| std::vector< [ConstBaseNodePtr](api/Classes/classginn_1_1_ptr.md) > | **[ins](api/Classes/classginn_1_1_base_node.md#function-ins)**() const |
| const [BaseNodePtr](api/Classes/classginn_1_1_ptr.md) & | **[in](api/Classes/classginn_1_1_base_node.md#function-in)**(size_t idx =0) |
| [ConstBaseNodePtr](api/Classes/classginn_1_1_ptr.md) | **[in](api/Classes/classginn_1_1_base_node.md#function-in)**(size_t idx =0) const |
| virtual void | **[set_ins](api/Classes/classginn_1_1_base_node.md#function-set_ins)**(const std::vector< [BaseNodePtr](api/Classes/classginn_1_1_ptr.md) > & ) |
| virtual | **[~BaseNode](api/Classes/classginn_1_1_base_node.md#function-~basenode)**() =default |
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


## Public Functions Documentation

### function dev

```cpp
inline virtual DevPtr dev() const override
```


**Reimplements**: [ginn::BaseNode::dev](api/Classes/classginn_1_1_base_node.md#function-dev)


### function shape

```cpp
inline virtual Shape shape() const override
```


**Reimplements**: [ginn::BaseNode::shape](api/Classes/classginn_1_1_base_node.md#function-shape)


### function name

```cpp
inline virtual std::string name() const override
```


**Reimplements**: [ginn::BaseNode::name](api/Classes/classginn_1_1_base_node.md#function-name)


### function BaseNode

```cpp
BaseNode() =default
```


### function BaseNode

```cpp
inline BaseNode(
    const std::vector< BaseNodePtr > & ins
)
```


### function BaseNode

```cpp
template <typename Container >
inline BaseNode(
    const Container & ins
)
```


-------------------------------

Updated on 2022-12-24 at 15:34:35 -0500
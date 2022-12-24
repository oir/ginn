# ginn::DimProdNode




Inherits from [ginn::DimNode](api/Classes/classginn_1_1_dim_node.md), [ginn::BaseNode](api/Classes/classginn_1_1_base_node.md)

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[DimProdNode](api/Classes/classginn_1_1_dim_prod_node.md#function-dimprodnode)**([DimPtr](api/Classes/classginn_1_1_ptr.md) left, [DimPtr](api/Classes/classginn_1_1_ptr.md) right) |
| virtual std::string | **[name](api/Classes/classginn_1_1_dim_prod_node.md#function-name)**() const override |

## Additional inherited members

**Public Functions inherited from [ginn::DimNode](api/Classes/classginn_1_1_dim_node.md)**

|                | Name           |
| -------------- | -------------- |
| | **[DimNode](api/Classes/classginn_1_1_dim_node.md#function-dimnode)**() =default |
| | **[DimNode](api/Classes/classginn_1_1_dim_node.md#function-dimnode)**(Size n) |
| | **[DimNode](api/Classes/classginn_1_1_dim_node.md#function-dimnode)**([BaseNodePtr](api/Classes/classginn_1_1_ptr.md) e, Size index) |
| virtual DevPtr | **[dev](api/Classes/classginn_1_1_dim_node.md#function-dev)**() const override |
| virtual bool | **[has_grad](api/Classes/classginn_1_1_dim_node.md#function-has_grad)**() const override |
| Size | **[value](api/Classes/classginn_1_1_dim_node.md#function-value)**() |
| virtual Shape | **[shape](api/Classes/classginn_1_1_dim_node.md#function-shape)**() const override |

**Protected Attributes inherited from [ginn::DimNode](api/Classes/classginn_1_1_dim_node.md)**

|                | Name           |
| -------------- | -------------- |
| Size | **[dim_](api/Classes/classginn_1_1_dim_node.md#variable-dim_)**  |
| Size | **[index_](api/Classes/classginn_1_1_dim_node.md#variable-index_)**  |

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

**Protected Functions inherited from [ginn::BaseNode](api/Classes/classginn_1_1_base_node.md)**

|                | Name           |
| -------------- | -------------- |
| virtual void | **[backward_](api/Classes/classginn_1_1_base_node.md#function-backward_)**() |

**Public Attributes inherited from [ginn::BaseNode](api/Classes/classginn_1_1_base_node.md)**

|                | Name           |
| -------------- | -------------- |
| bool | **[forwarded](api/Classes/classginn_1_1_base_node.md#variable-forwarded)**  |

**Protected Attributes inherited from [ginn::BaseNode](api/Classes/classginn_1_1_base_node.md)**

|                | Name           |
| -------------- | -------------- |
| std::vector< [BaseNodePtr](api/Classes/classginn_1_1_ptr.md) > | **[ins_](api/Classes/classginn_1_1_base_node.md#variable-ins_)**  |


## Public Functions Documentation

### function DimProdNode

```cpp
inline DimProdNode(
    DimPtr left,
    DimPtr right
)
```


### function name

```cpp
inline virtual std::string name() const override
```


**Reimplements**: [ginn::DimNode::name](api/Classes/classginn_1_1_dim_node.md#function-name)


-------------------------------

Updated on 2022-12-24 at 14:52:49 -0500
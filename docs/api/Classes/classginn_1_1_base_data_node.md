# ginn::BaseDataNode


 [More...](#detailed-description)

Inherits from [ginn::Node< Real >](api/Classes/classginn_1_1_node.md), [ginn::BaseNode](api/Classes/classginn_1_1_base_node.md)

Inherited by [ginn::ConstantLikeNode< Scalar >](api/Classes/classginn_1_1_constant_like_node.md), [ginn::DataNode< Scalar >](api/Classes/classginn_1_1_data_node.md), [ginn::UpperTriNode< Scalar >](api/Classes/classginn_1_1_upper_tri_node.md)

## Public Functions

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
| virtual std::string | **[name](api/Classes/classginn_1_1_base_data_node.md#function-name)**() const override =0 |

## Additional inherited members

**Public Types inherited from [ginn::Node< Real >](api/Classes/classginn_1_1_node.md)**

|                | Name           |
| -------------- | -------------- |
| using ScalarType | **[Scalar](api/Classes/classginn_1_1_node.md#using-scalar)**  |

**Public Functions inherited from [ginn::Node< Real >](api/Classes/classginn_1_1_node.md)**

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
| virtual void | **[init_grad](api/Classes/classginn_1_1_base_node.md#function-init_grad)**() |
| virtual void | **[reset_grad](api/Classes/classginn_1_1_base_node.md#function-reset_grad)**() |
| virtual void | **[reset_forwarded](api/Classes/classginn_1_1_base_node.md#function-reset_forwarded)**() |

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
class ginn::BaseDataNode;
```

## Public Functions Documentation

### function BaseDataNode

```cpp
inline BaseDataNode(
    DevPtr dev,
    const std::vector< BaseNodePtr > & ins
)
```


### function BaseDataNode

```cpp
inline BaseDataNode(
    DevPtr dev,
    const Shape & shape,
    const std::vector< BaseNodePtr > & ins
)
```


### function BaseDataNode

```cpp
template <typename NodeType >
inline BaseDataNode(
    const std::vector< NodeType > & ins
)
```


### function BaseDataNode

```cpp
inline BaseDataNode(
    DevPtr dev =cpu()
)
```


### function BaseDataNode

```cpp
inline BaseDataNode(
    const Shape & shape
)
```


### function BaseDataNode

```cpp
inline BaseDataNode(
    DevPtr dev,
    const Shape & shape
)
```


### function BaseDataNode

```cpp
inline BaseDataNode(
    const std::initializer_list< BaseNodePtr > & ins
)
```


### function BaseDataNode

```cpp
inline BaseDataNode(
    DevPtr dev,
    const std::initializer_list< BaseNodePtr > & ins
)
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


**Reimplemented by**: [ginn::UpperTriNode::has_grad](api/Classes/classginn_1_1_upper_tri_node.md#function-has_grad)


### function has_grad

```cpp
inline virtual void has_grad(
    bool hg
)
```


### function name

```cpp
virtual std::string name() const override =0
```


**Reimplements**: [ginn::BaseNode::name](api/Classes/classginn_1_1_base_node.md#function-name)


**Reimplemented by**: [ginn::AffineNode::name](api/Classes/classginn_1_1_affine_node.md#function-name), [ginn::AddScalarNode::name](api/Classes/classginn_1_1_add_scalar_node.md#function-name), [ginn::SubtractScalarNode::name](api/Classes/classginn_1_1_subtract_scalar_node.md#function-name), [ginn::AddNode::name](api/Classes/classginn_1_1_add_node.md#function-name), [ginn::SubtractNode::name](api/Classes/classginn_1_1_subtract_node.md#function-name), [ginn::ProdScalarNode::name](api/Classes/classginn_1_1_prod_scalar_node.md#function-name), [ginn::CwiseProdNode::name](api/Classes/classginn_1_1_cwise_prod_node.md#function-name), [ginn::CwiseProdAddNode::name](api/Classes/classginn_1_1_cwise_prod_add_node.md#function-name), [ginn::CwiseMaxNode::name](api/Classes/classginn_1_1_cwise_max_node.md#function-name), [ginn::DropoutNode::name](api/Classes/classginn_1_1_dropout_node.md#function-name), [ginn::LessThanNode::name](api/Classes/classginn_1_1_less_than_node.md#function-name), [ginn::Conv2dNode::name](api/Classes/classginn_1_1_conv2d_node.md#function-name), [ginn::Conv1dNode::name](api/Classes/classginn_1_1_conv1d_node.md#function-name), [ginn::DataNode::name](api/Classes/classginn_1_1_data_node.md#function-name), [ginn::ConstantLikeNode::name](api/Classes/classginn_1_1_constant_like_node.md#function-name), [ginn::InPlaceAddNode::name](api/Classes/classginn_1_1_in_place_add_node.md#function-name), [ginn::InPlaceAddScalarNode::name](api/Classes/classginn_1_1_in_place_add_scalar_node.md#function-name), [ginn::InPlaceCwiseProdNode::name](api/Classes/classginn_1_1_in_place_cwise_prod_node.md#function-name), [ginn::InPlaceProdScalarNode::name](api/Classes/classginn_1_1_in_place_prod_scalar_node.md#function-name), [ginn::InPlaceDropoutNode::name](api/Classes/classginn_1_1_in_place_dropout_node.md#function-name), [ginn::InPlaceMaskNode::name](api/Classes/classginn_1_1_in_place_mask_node.md#function-name), [ginn::InPlaceLayerNormNode::name](api/Classes/classginn_1_1_in_place_layer_norm_node.md#function-name), [ginn::InPlacePermuteNode::name](api/Classes/classginn_1_1_in_place_permute_node.md#function-name), [ginn::LayerNormNode::name](api/Classes/classginn_1_1_layer_norm_node.md#function-name), [ginn::DeviceTransferNode::name](api/Classes/classginn_1_1_device_transfer_node.md#function-name), [ginn::CatNode::name](api/Classes/classginn_1_1_cat_node.md#function-name), [ginn::RowwiseCatNode::name](api/Classes/classginn_1_1_rowwise_cat_node.md#function-name), [ginn::RowwiseUncatNode::name](api/Classes/classginn_1_1_rowwise_uncat_node.md#function-name), [ginn::StackNode::name](api/Classes/classginn_1_1_stack_node.md#function-name), [ginn::ReshapeNode::name](api/Classes/classginn_1_1_reshape_node.md#function-name), [ginn::RankViewNode::name](api/Classes/classginn_1_1_rank_view_node.md#function-name), [ginn::SliceNode::name](api/Classes/classginn_1_1_slice_node.md#function-name), [ginn::ChipNode::name](api/Classes/classginn_1_1_chip_node.md#function-name), [ginn::MapNode::name](api/Classes/classginn_1_1_map_node.md#function-name), [ginn::PermuteNode::name](api/Classes/classginn_1_1_permute_node.md#function-name), [ginn::RowBroadcastNode::name](api/Classes/classginn_1_1_row_broadcast_node.md#function-name), [ginn::ColBroadcastNode::name](api/Classes/classginn_1_1_col_broadcast_node.md#function-name), [ginn::UpperTriNode::name](api/Classes/classginn_1_1_upper_tri_node.md#function-name), [ginn::PickNode::name](api/Classes/classginn_1_1_pick_node.md#function-name), [ginn::PickSoftmaxNode::name](api/Classes/classginn_1_1_pick_softmax_node.md#function-name), [ginn::PickNegLogSoftmaxNode::name](api/Classes/classginn_1_1_pick_neg_log_softmax_node.md#function-name), [ginn::PickNegLogSigmoidNode::name](api/Classes/classginn_1_1_pick_neg_log_sigmoid_node.md#function-name), [ginn::MaxPool2dNode::name](api/Classes/classginn_1_1_max_pool2d_node.md#function-name), [ginn::MaxPool1dNode::name](api/Classes/classginn_1_1_max_pool1d_node.md#function-name), [ginn::ProdNode::name](api/Classes/classginn_1_1_prod_node.md#function-name), [ginn::BatchedProdNode::name](api/Classes/classginn_1_1_batched_prod_node.md#function-name), [ginn::SumNode::name](api/Classes/classginn_1_1_sum_node.md#function-name), [ginn::AxisSumNode::name](api/Classes/classginn_1_1_axis_sum_node.md#function-name), [ginn::MeanNode::name](api/Classes/classginn_1_1_mean_node.md#function-name), [ginn::VarianceNode::name](api/Classes/classginn_1_1_variance_node.md#function-name), [ginn::SelectNode::name](api/Classes/classginn_1_1_select_node.md#function-name), [ginn::MaskNode::name](api/Classes/classginn_1_1_mask_node.md#function-name)


-------------------------------

Updated on 2022-12-24 at 14:52:49 -0500
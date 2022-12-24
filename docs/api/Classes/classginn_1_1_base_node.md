# ginn::BaseNode




Inherited by [ginn::Node< Scalar >](api/Classes/classginn_1_1_node.md), [ginn::Node< Real >](api/Classes/classginn_1_1_node.md), [ginn::Node< bool >](api/Classes/classginn_1_1_node.md), [ginn::DimNode](api/Classes/classginn_1_1_dim_node.md), [ginn::Node< ScalarType >](api/Classes/classginn_1_1_node.md), [ginn::SinkNode](api/Classes/classginn_1_1_sink_node.md)

## Public Functions

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
| virtual std::string | **[name](api/Classes/classginn_1_1_base_node.md#function-name)**() const =0 |


</span>

## Protected Functions

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| virtual void | **[forward_](api/Classes/classginn_1_1_base_node.md#function-forward_)**() |
| virtual void | **[backward_](api/Classes/classginn_1_1_base_node.md#function-backward_)**() |


</span>

## Public Attributes

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| bool | **[forwarded](api/Classes/classginn_1_1_base_node.md#variable-forwarded)**  |


</span>

## Protected Attributes

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| std::vector< [BaseNodePtr](api/Classes/classginn_1_1_ptr.md) > | **[ins_](api/Classes/classginn_1_1_base_node.md#variable-ins_)**  |


</span>

## Public Functions Documentation

### function BaseNode

```cpp
BaseNode() =default
```


### function ins

```cpp
inline const auto & ins()
```


### function ins

```cpp
inline std::vector< ConstBaseNodePtr > ins() const
```


### function in

```cpp
inline const BaseNodePtr & in(
    size_t idx =0
)
```


### function in

```cpp
inline ConstBaseNodePtr in(
    size_t idx =0
) const
```


### function set_ins

```cpp
inline virtual void set_ins(
    const std::vector< BaseNodePtr > & 
)
```


**Reimplemented by**: [ginn::AffineNode::set_ins](api/Classes/classginn_1_1_affine_node.md#function-set_ins), [ginn::AddNode::set_ins](api/Classes/classginn_1_1_add_node.md#function-set_ins), [ginn::MapNode::set_ins](api/Classes/classginn_1_1_map_node.md#function-set_ins), [ginn::ProdNode::set_ins](api/Classes/classginn_1_1_prod_node.md#function-set_ins), [ginn::SumNode::set_ins](api/Classes/classginn_1_1_sum_node.md#function-set_ins)


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


### function ~BaseNode

```cpp
virtual ~BaseNode() =default
```


### function dev

```cpp
virtual DevPtr dev() const =0
```


**Reimplemented by**: [ginn::Node::dev](api/Classes/classginn_1_1_node.md#function-dev), [ginn::Node::dev](api/Classes/classginn_1_1_node.md#function-dev), [ginn::Node::dev](api/Classes/classginn_1_1_node.md#function-dev), [ginn::Node::dev](api/Classes/classginn_1_1_node.md#function-dev), [ginn::SinkNode::dev](api/Classes/classginn_1_1_sink_node.md#function-dev), [ginn::DimNode::dev](api/Classes/classginn_1_1_dim_node.md#function-dev), [ginn::DeviceViewNode::dev](api/Classes/classginn_1_1_device_view_node.md#function-dev)


### function shape

```cpp
virtual Shape shape() const =0
```


**Reimplemented by**: [ginn::Node::shape](api/Classes/classginn_1_1_node.md#function-shape), [ginn::Node::shape](api/Classes/classginn_1_1_node.md#function-shape), [ginn::Node::shape](api/Classes/classginn_1_1_node.md#function-shape), [ginn::Node::shape](api/Classes/classginn_1_1_node.md#function-shape), [ginn::DataNode::shape](api/Classes/classginn_1_1_data_node.md#function-shape), [ginn::SinkNode::shape](api/Classes/classginn_1_1_sink_node.md#function-shape), [ginn::DimNode::shape](api/Classes/classginn_1_1_dim_node.md#function-shape), [ginn::WeightNode::shape](api/Classes/classginn_1_1_weight_node.md#function-shape)


### function shape2

```cpp
inline Shape shape2() const
```


### function rows

```cpp
inline Size rows() const
```


### function cols

```cpp
inline Size cols() const
```


### function size

```cpp
inline Size size() const
```


### function forward

```cpp
inline void forward()
```


### function backward

```cpp
inline void backward()
```


### function has_grad

```cpp
inline virtual bool has_grad() const
```


**Reimplemented by**: [ginn::LessThanNode::has_grad](api/Classes/classginn_1_1_less_than_node.md#function-has_grad), [ginn::BaseDataNode::has_grad](api/Classes/classginn_1_1_base_data_node.md#function-has_grad), [ginn::BaseDataNode::has_grad](api/Classes/classginn_1_1_base_data_node.md#function-has_grad), [ginn::BaseDataNode::has_grad](api/Classes/classginn_1_1_base_data_node.md#function-has_grad), [ginn::BaseDataNode::has_grad](api/Classes/classginn_1_1_base_data_node.md#function-has_grad), [ginn::InPlaceAddNode::has_grad](api/Classes/classginn_1_1_in_place_add_node.md#function-has_grad), [ginn::InPlaceAddScalarNode::has_grad](api/Classes/classginn_1_1_in_place_add_scalar_node.md#function-has_grad), [ginn::InPlaceCwiseProdNode::has_grad](api/Classes/classginn_1_1_in_place_cwise_prod_node.md#function-has_grad), [ginn::InPlaceProdScalarNode::has_grad](api/Classes/classginn_1_1_in_place_prod_scalar_node.md#function-has_grad), [ginn::InPlaceDropoutNode::has_grad](api/Classes/classginn_1_1_in_place_dropout_node.md#function-has_grad), [ginn::InPlaceMaskNode::has_grad](api/Classes/classginn_1_1_in_place_mask_node.md#function-has_grad), [ginn::InPlaceLayerNormNode::has_grad](api/Classes/classginn_1_1_in_place_layer_norm_node.md#function-has_grad), [ginn::InPlacePermuteNode::has_grad](api/Classes/classginn_1_1_in_place_permute_node.md#function-has_grad), [ginn::DimNode::has_grad](api/Classes/classginn_1_1_dim_node.md#function-has_grad), [ginn::DeviceTransferNode::has_grad](api/Classes/classginn_1_1_device_transfer_node.md#function-has_grad), [ginn::RowwiseUncatNode::has_grad](api/Classes/classginn_1_1_rowwise_uncat_node.md#function-has_grad), [ginn::ReshapeNode::has_grad](api/Classes/classginn_1_1_reshape_node.md#function-has_grad), [ginn::RankViewNode::has_grad](api/Classes/classginn_1_1_rank_view_node.md#function-has_grad), [ginn::MapNode::has_grad](api/Classes/classginn_1_1_map_node.md#function-has_grad), [ginn::ColBroadcastNode::has_grad](api/Classes/classginn_1_1_col_broadcast_node.md#function-has_grad), [ginn::UpperTriNode::has_grad](api/Classes/classginn_1_1_upper_tri_node.md#function-has_grad), [ginn::WeightNode::has_grad](api/Classes/classginn_1_1_weight_node.md#function-has_grad)


### function init_grad

```cpp
inline virtual void init_grad()
```


**Reimplemented by**: [ginn::Node::init_grad](api/Classes/classginn_1_1_node.md#function-init_grad), [ginn::Node::init_grad](api/Classes/classginn_1_1_node.md#function-init_grad), [ginn::Node::init_grad](api/Classes/classginn_1_1_node.md#function-init_grad), [ginn::Node::init_grad](api/Classes/classginn_1_1_node.md#function-init_grad), [ginn::InPlacePermuteNode::init_grad](api/Classes/classginn_1_1_in_place_permute_node.md#function-init_grad), [ginn::RowwiseUncatNode::init_grad](api/Classes/classginn_1_1_rowwise_uncat_node.md#function-init_grad), [ginn::ReshapeNode::init_grad](api/Classes/classginn_1_1_reshape_node.md#function-init_grad), [ginn::RankViewNode::init_grad](api/Classes/classginn_1_1_rank_view_node.md#function-init_grad), [ginn::ColBroadcastNode::init_grad](api/Classes/classginn_1_1_col_broadcast_node.md#function-init_grad)


### function reset_grad

```cpp
inline virtual void reset_grad()
```


**Reimplemented by**: [ginn::Node::reset_grad](api/Classes/classginn_1_1_node.md#function-reset_grad), [ginn::Node::reset_grad](api/Classes/classginn_1_1_node.md#function-reset_grad), [ginn::Node::reset_grad](api/Classes/classginn_1_1_node.md#function-reset_grad), [ginn::Node::reset_grad](api/Classes/classginn_1_1_node.md#function-reset_grad)


### function reset_forwarded

```cpp
inline virtual void reset_forwarded()
```


**Reimplemented by**: [ginn::DataNode::reset_forwarded](api/Classes/classginn_1_1_data_node.md#function-reset_forwarded), [ginn::WeightNode::reset_forwarded](api/Classes/classginn_1_1_weight_node.md#function-reset_forwarded)


### function name

```cpp
virtual std::string name() const =0
```


**Reimplemented by**: [ginn::AffineNode::name](api/Classes/classginn_1_1_affine_node.md#function-name), [ginn::AddScalarNode::name](api/Classes/classginn_1_1_add_scalar_node.md#function-name), [ginn::SubtractScalarNode::name](api/Classes/classginn_1_1_subtract_scalar_node.md#function-name), [ginn::AddNode::name](api/Classes/classginn_1_1_add_node.md#function-name), [ginn::SubtractNode::name](api/Classes/classginn_1_1_subtract_node.md#function-name), [ginn::ProdScalarNode::name](api/Classes/classginn_1_1_prod_scalar_node.md#function-name), [ginn::CwiseProdNode::name](api/Classes/classginn_1_1_cwise_prod_node.md#function-name), [ginn::CwiseProdAddNode::name](api/Classes/classginn_1_1_cwise_prod_add_node.md#function-name), [ginn::CwiseMaxNode::name](api/Classes/classginn_1_1_cwise_max_node.md#function-name), [ginn::DropoutNode::name](api/Classes/classginn_1_1_dropout_node.md#function-name), [ginn::LessThanNode::name](api/Classes/classginn_1_1_less_than_node.md#function-name), [ginn::Conv2dNode::name](api/Classes/classginn_1_1_conv2d_node.md#function-name), [ginn::Conv1dNode::name](api/Classes/classginn_1_1_conv1d_node.md#function-name), [ginn::DataNode::name](api/Classes/classginn_1_1_data_node.md#function-name), [ginn::ConstantLikeNode::name](api/Classes/classginn_1_1_constant_like_node.md#function-name), [ginn::InPlaceAddNode::name](api/Classes/classginn_1_1_in_place_add_node.md#function-name), [ginn::InPlaceAddScalarNode::name](api/Classes/classginn_1_1_in_place_add_scalar_node.md#function-name), [ginn::InPlaceCwiseProdNode::name](api/Classes/classginn_1_1_in_place_cwise_prod_node.md#function-name), [ginn::InPlaceProdScalarNode::name](api/Classes/classginn_1_1_in_place_prod_scalar_node.md#function-name), [ginn::InPlaceDropoutNode::name](api/Classes/classginn_1_1_in_place_dropout_node.md#function-name), [ginn::InPlaceMaskNode::name](api/Classes/classginn_1_1_in_place_mask_node.md#function-name), [ginn::InPlaceLayerNormNode::name](api/Classes/classginn_1_1_in_place_layer_norm_node.md#function-name), [ginn::InPlacePermuteNode::name](api/Classes/classginn_1_1_in_place_permute_node.md#function-name), [ginn::LayerNormNode::name](api/Classes/classginn_1_1_layer_norm_node.md#function-name), [ginn::SinkNode::name](api/Classes/classginn_1_1_sink_node.md#function-name), [ginn::DimNode::name](api/Classes/classginn_1_1_dim_node.md#function-name), [ginn::DimProdNode::name](api/Classes/classginn_1_1_dim_prod_node.md#function-name), [ginn::DeviceViewNode::name](api/Classes/classginn_1_1_device_view_node.md#function-name), [ginn::DeviceTransferNode::name](api/Classes/classginn_1_1_device_transfer_node.md#function-name), [ginn::CatNode::name](api/Classes/classginn_1_1_cat_node.md#function-name), [ginn::RowwiseCatNode::name](api/Classes/classginn_1_1_rowwise_cat_node.md#function-name), [ginn::RowwiseUncatNode::name](api/Classes/classginn_1_1_rowwise_uncat_node.md#function-name), [ginn::StackNode::name](api/Classes/classginn_1_1_stack_node.md#function-name), [ginn::ReshapeNode::name](api/Classes/classginn_1_1_reshape_node.md#function-name), [ginn::RankViewNode::name](api/Classes/classginn_1_1_rank_view_node.md#function-name), [ginn::SliceNode::name](api/Classes/classginn_1_1_slice_node.md#function-name), [ginn::ChipNode::name](api/Classes/classginn_1_1_chip_node.md#function-name), [ginn::MapNode::name](api/Classes/classginn_1_1_map_node.md#function-name), [ginn::PermuteNode::name](api/Classes/classginn_1_1_permute_node.md#function-name), [ginn::RowBroadcastNode::name](api/Classes/classginn_1_1_row_broadcast_node.md#function-name), [ginn::ColBroadcastNode::name](api/Classes/classginn_1_1_col_broadcast_node.md#function-name), [ginn::UpperTriNode::name](api/Classes/classginn_1_1_upper_tri_node.md#function-name), [ginn::PickNode::name](api/Classes/classginn_1_1_pick_node.md#function-name), [ginn::PickSoftmaxNode::name](api/Classes/classginn_1_1_pick_softmax_node.md#function-name), [ginn::PickNegLogSoftmaxNode::name](api/Classes/classginn_1_1_pick_neg_log_softmax_node.md#function-name), [ginn::PickNegLogSigmoidNode::name](api/Classes/classginn_1_1_pick_neg_log_sigmoid_node.md#function-name), [ginn::MaxPool2dNode::name](api/Classes/classginn_1_1_max_pool2d_node.md#function-name), [ginn::MaxPool1dNode::name](api/Classes/classginn_1_1_max_pool1d_node.md#function-name), [ginn::ProdNode::name](api/Classes/classginn_1_1_prod_node.md#function-name), [ginn::BatchedProdNode::name](api/Classes/classginn_1_1_batched_prod_node.md#function-name), [ginn::SumNode::name](api/Classes/classginn_1_1_sum_node.md#function-name), [ginn::AxisSumNode::name](api/Classes/classginn_1_1_axis_sum_node.md#function-name), [ginn::MeanNode::name](api/Classes/classginn_1_1_mean_node.md#function-name), [ginn::VarianceNode::name](api/Classes/classginn_1_1_variance_node.md#function-name), [ginn::SelectNode::name](api/Classes/classginn_1_1_select_node.md#function-name), [ginn::MaskNode::name](api/Classes/classginn_1_1_mask_node.md#function-name), [ginn::WeightNode::name](api/Classes/classginn_1_1_weight_node.md#function-name), [ginn::BaseDataNode::name](api/Classes/classginn_1_1_base_data_node.md#function-name), [ginn::BaseDataNode::name](api/Classes/classginn_1_1_base_data_node.md#function-name), [ginn::BaseDataNode::name](api/Classes/classginn_1_1_base_data_node.md#function-name), [ginn::BaseDataNode::name](api/Classes/classginn_1_1_base_data_node.md#function-name)


## Protected Functions Documentation

### function forward_

```cpp
inline virtual void forward_()
```


**Reimplemented by**: [ginn::AffineNode::forward_](api/Classes/classginn_1_1_affine_node.md#function-forward_), [ginn::AddScalarNode::forward_](api/Classes/classginn_1_1_add_scalar_node.md#function-forward_), [ginn::SubtractScalarNode::forward_](api/Classes/classginn_1_1_subtract_scalar_node.md#function-forward_), [ginn::AddNode::forward_](api/Classes/classginn_1_1_add_node.md#function-forward_), [ginn::SubtractNode::forward_](api/Classes/classginn_1_1_subtract_node.md#function-forward_), [ginn::ProdScalarNode::forward_](api/Classes/classginn_1_1_prod_scalar_node.md#function-forward_), [ginn::CwiseProdNode::forward_](api/Classes/classginn_1_1_cwise_prod_node.md#function-forward_), [ginn::CwiseProdAddNode::forward_](api/Classes/classginn_1_1_cwise_prod_add_node.md#function-forward_), [ginn::CwiseMaxNode::forward_](api/Classes/classginn_1_1_cwise_max_node.md#function-forward_), [ginn::DropoutNode::forward_](api/Classes/classginn_1_1_dropout_node.md#function-forward_), [ginn::LessThanNode::forward_](api/Classes/classginn_1_1_less_than_node.md#function-forward_), [ginn::Conv2dNode::forward_](api/Classes/classginn_1_1_conv2d_node.md#function-forward_), [ginn::Conv1dNode::forward_](api/Classes/classginn_1_1_conv1d_node.md#function-forward_), [ginn::ConstantLikeNode::forward_](api/Classes/classginn_1_1_constant_like_node.md#function-forward_), [ginn::InPlaceAddNode::forward_](api/Classes/classginn_1_1_in_place_add_node.md#function-forward_), [ginn::InPlaceMaskNode::forward_](api/Classes/classginn_1_1_in_place_mask_node.md#function-forward_), [ginn::InPlacePermuteNode::forward_](api/Classes/classginn_1_1_in_place_permute_node.md#function-forward_), [ginn::LayerNormNode::forward_](api/Classes/classginn_1_1_layer_norm_node.md#function-forward_), [ginn::DimNode::forward_](api/Classes/classginn_1_1_dim_node.md#function-forward_), [ginn::DimProdNode::forward_](api/Classes/classginn_1_1_dim_prod_node.md#function-forward_), [ginn::DeviceTransferNode::forward_](api/Classes/classginn_1_1_device_transfer_node.md#function-forward_), [ginn::CatNode::forward_](api/Classes/classginn_1_1_cat_node.md#function-forward_), [ginn::RowwiseCatNode::forward_](api/Classes/classginn_1_1_rowwise_cat_node.md#function-forward_), [ginn::RowwiseUncatNode::forward_](api/Classes/classginn_1_1_rowwise_uncat_node.md#function-forward_), [ginn::StackNode::forward_](api/Classes/classginn_1_1_stack_node.md#function-forward_), [ginn::ReshapeNode::forward_](api/Classes/classginn_1_1_reshape_node.md#function-forward_), [ginn::RankViewNode::forward_](api/Classes/classginn_1_1_rank_view_node.md#function-forward_), [ginn::SliceNode::forward_](api/Classes/classginn_1_1_slice_node.md#function-forward_), [ginn::ChipNode::forward_](api/Classes/classginn_1_1_chip_node.md#function-forward_), [ginn::PermuteNode::forward_](api/Classes/classginn_1_1_permute_node.md#function-forward_), [ginn::RowBroadcastNode::forward_](api/Classes/classginn_1_1_row_broadcast_node.md#function-forward_), [ginn::ColBroadcastNode::forward_](api/Classes/classginn_1_1_col_broadcast_node.md#function-forward_), [ginn::UpperTriNode::forward_](api/Classes/classginn_1_1_upper_tri_node.md#function-forward_), [ginn::PickNode::forward_](api/Classes/classginn_1_1_pick_node.md#function-forward_), [ginn::PickSoftmaxNode::forward_](api/Classes/classginn_1_1_pick_softmax_node.md#function-forward_), [ginn::PickNegLogSoftmaxNode::forward_](api/Classes/classginn_1_1_pick_neg_log_softmax_node.md#function-forward_), [ginn::PickNegLogSigmoidNode::forward_](api/Classes/classginn_1_1_pick_neg_log_sigmoid_node.md#function-forward_), [ginn::MaxPool2dNode::forward_](api/Classes/classginn_1_1_max_pool2d_node.md#function-forward_), [ginn::MaxPool1dNode::forward_](api/Classes/classginn_1_1_max_pool1d_node.md#function-forward_), [ginn::ProdNode::forward_](api/Classes/classginn_1_1_prod_node.md#function-forward_), [ginn::BatchedProdNode::forward_](api/Classes/classginn_1_1_batched_prod_node.md#function-forward_), [ginn::SumNode::forward_](api/Classes/classginn_1_1_sum_node.md#function-forward_), [ginn::AxisSumNode::forward_](api/Classes/classginn_1_1_axis_sum_node.md#function-forward_), [ginn::MeanNode::forward_](api/Classes/classginn_1_1_mean_node.md#function-forward_), [ginn::VarianceNode::forward_](api/Classes/classginn_1_1_variance_node.md#function-forward_), [ginn::SelectNode::forward_](api/Classes/classginn_1_1_select_node.md#function-forward_), [ginn::MaskNode::forward_](api/Classes/classginn_1_1_mask_node.md#function-forward_)


### function backward_

```cpp
inline virtual void backward_()
```


**Reimplemented by**: [ginn::AffineNode::backward_](api/Classes/classginn_1_1_affine_node.md#function-backward_), [ginn::AddScalarNode::backward_](api/Classes/classginn_1_1_add_scalar_node.md#function-backward_), [ginn::SubtractScalarNode::backward_](api/Classes/classginn_1_1_subtract_scalar_node.md#function-backward_), [ginn::AddNode::backward_](api/Classes/classginn_1_1_add_node.md#function-backward_), [ginn::SubtractNode::backward_](api/Classes/classginn_1_1_subtract_node.md#function-backward_), [ginn::ProdScalarNode::backward_](api/Classes/classginn_1_1_prod_scalar_node.md#function-backward_), [ginn::CwiseProdNode::backward_](api/Classes/classginn_1_1_cwise_prod_node.md#function-backward_), [ginn::CwiseProdAddNode::backward_](api/Classes/classginn_1_1_cwise_prod_add_node.md#function-backward_), [ginn::CwiseMaxNode::backward_](api/Classes/classginn_1_1_cwise_max_node.md#function-backward_), [ginn::DropoutNode::backward_](api/Classes/classginn_1_1_dropout_node.md#function-backward_), [ginn::Conv2dNode::backward_](api/Classes/classginn_1_1_conv2d_node.md#function-backward_), [ginn::Conv1dNode::backward_](api/Classes/classginn_1_1_conv1d_node.md#function-backward_), [ginn::InPlaceAddNode::backward_](api/Classes/classginn_1_1_in_place_add_node.md#function-backward_), [ginn::InPlaceAddScalarNode::backward_](api/Classes/classginn_1_1_in_place_add_scalar_node.md#function-backward_), [ginn::InPlaceCwiseProdNode::backward_](api/Classes/classginn_1_1_in_place_cwise_prod_node.md#function-backward_), [ginn::InPlaceProdScalarNode::backward_](api/Classes/classginn_1_1_in_place_prod_scalar_node.md#function-backward_), [ginn::InPlaceDropoutNode::backward_](api/Classes/classginn_1_1_in_place_dropout_node.md#function-backward_), [ginn::InPlaceMaskNode::backward_](api/Classes/classginn_1_1_in_place_mask_node.md#function-backward_), [ginn::InPlaceLayerNormNode::backward_](api/Classes/classginn_1_1_in_place_layer_norm_node.md#function-backward_), [ginn::LayerNormNode::backward_](api/Classes/classginn_1_1_layer_norm_node.md#function-backward_), [ginn::DeviceTransferNode::backward_](api/Classes/classginn_1_1_device_transfer_node.md#function-backward_), [ginn::CatNode::backward_](api/Classes/classginn_1_1_cat_node.md#function-backward_), [ginn::RowwiseCatNode::backward_](api/Classes/classginn_1_1_rowwise_cat_node.md#function-backward_), [ginn::StackNode::backward_](api/Classes/classginn_1_1_stack_node.md#function-backward_), [ginn::RankViewNode::backward_](api/Classes/classginn_1_1_rank_view_node.md#function-backward_), [ginn::SliceNode::backward_](api/Classes/classginn_1_1_slice_node.md#function-backward_), [ginn::ChipNode::backward_](api/Classes/classginn_1_1_chip_node.md#function-backward_), [ginn::PermuteNode::backward_](api/Classes/classginn_1_1_permute_node.md#function-backward_), [ginn::RowBroadcastNode::backward_](api/Classes/classginn_1_1_row_broadcast_node.md#function-backward_), [ginn::ColBroadcastNode::backward_](api/Classes/classginn_1_1_col_broadcast_node.md#function-backward_), [ginn::PickNode::backward_](api/Classes/classginn_1_1_pick_node.md#function-backward_), [ginn::PickSoftmaxNode::backward_](api/Classes/classginn_1_1_pick_softmax_node.md#function-backward_), [ginn::PickNegLogSoftmaxNode::backward_](api/Classes/classginn_1_1_pick_neg_log_softmax_node.md#function-backward_), [ginn::PickNegLogSigmoidNode::backward_](api/Classes/classginn_1_1_pick_neg_log_sigmoid_node.md#function-backward_), [ginn::MaxPool2dNode::backward_](api/Classes/classginn_1_1_max_pool2d_node.md#function-backward_), [ginn::MaxPool1dNode::backward_](api/Classes/classginn_1_1_max_pool1d_node.md#function-backward_), [ginn::ProdNode::backward_](api/Classes/classginn_1_1_prod_node.md#function-backward_), [ginn::BatchedProdNode::backward_](api/Classes/classginn_1_1_batched_prod_node.md#function-backward_), [ginn::SumNode::backward_](api/Classes/classginn_1_1_sum_node.md#function-backward_), [ginn::AxisSumNode::backward_](api/Classes/classginn_1_1_axis_sum_node.md#function-backward_), [ginn::MeanNode::backward_](api/Classes/classginn_1_1_mean_node.md#function-backward_), [ginn::VarianceNode::backward_](api/Classes/classginn_1_1_variance_node.md#function-backward_), [ginn::SelectNode::backward_](api/Classes/classginn_1_1_select_node.md#function-backward_), [ginn::MaskNode::backward_](api/Classes/classginn_1_1_mask_node.md#function-backward_)


## Public Attributes Documentation

### variable forwarded

```cpp
bool forwarded = false;
```


## Protected Attributes Documentation

### variable ins_

```cpp
std::vector< BaseNodePtr > ins_;
```


-------------------------------

Updated on 2022-12-24 at 15:34:35 -0500
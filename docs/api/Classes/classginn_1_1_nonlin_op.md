# ginn::NonlinOp


 [More...](#detailed-description)

Inherited by [ginn::Gelu2Op< Scalar >](api/Classes/classginn_1_1_gelu2_op.md), [ginn::GeluOp< Scalar >](api/Classes/classginn_1_1_gelu_op.md), [ginn::IdentityOp< Scalar >](api/Classes/classginn_1_1_identity_op.md), [ginn::LogOp< Scalar >](api/Classes/classginn_1_1_log_op.md), [ginn::ReluOp< Scalar >](api/Classes/classginn_1_1_relu_op.md), [ginn::SigmoidOp< Scalar >](api/Classes/classginn_1_1_sigmoid_op.md), [ginn::SoftmaxOp< Scalar >](api/Classes/classginn_1_1_softmax_op.md), [ginn::SqrtOp< Scalar >](api/Classes/classginn_1_1_sqrt_op.md), [ginn::TanhOp< Scalar >](api/Classes/classginn_1_1_tanh_op.md)

## Public Functions

|                | Name           |
| -------------- | -------------- |
| virtual bool | **[backward_requires_input](api/Classes/classginn_1_1_nonlin_op.md#function-backward_requires_input)**() const |
| virtual bool | **[is_identity](api/Classes/classginn_1_1_nonlin_op.md#function-is_identity)**() const |
| virtual void | **[forward](api/Classes/classginn_1_1_nonlin_op.md#function-forward)**([Tensor](api/Classes/classginn_1_1_tensor.md)< Scalar > & , const [Tensor](api/Classes/classginn_1_1_tensor.md)< Scalar > & ) const =0 |
| virtual void | **[backward](api/Classes/classginn_1_1_nonlin_op.md#function-backward)**([Tensor](api/Classes/classginn_1_1_tensor.md)< Scalar > & , const [Tensor](api/Classes/classginn_1_1_tensor.md)< Scalar > & , const [Tensor](api/Classes/classginn_1_1_tensor.md)< Scalar > & , const [Tensor](api/Classes/classginn_1_1_tensor.md)< Scalar > & , bool ) const =0 |
| virtual | **[~NonlinOp](api/Classes/classginn_1_1_nonlin_op.md#function-~nonlinop)**() =default |
| virtual std::unique_ptr< [NonlinOp](api/Classes/classginn_1_1_nonlin_op.md)< Scalar > > | **[copy](api/Classes/classginn_1_1_nonlin_op.md#function-copy)**() const =0 |

## Detailed Description

```cpp
template <typename Scalar >
class ginn::NonlinOp;
```

## Public Functions Documentation

### function backward_requires_input

```cpp
inline virtual bool backward_requires_input() const
```


**Reimplemented by**: [ginn::IdentityOp::backward_requires_input](api/Classes/classginn_1_1_identity_op.md#function-backward_requires_input), [ginn::TanhOp::backward_requires_input](api/Classes/classginn_1_1_tanh_op.md#function-backward_requires_input), [ginn::ReluOp::backward_requires_input](api/Classes/classginn_1_1_relu_op.md#function-backward_requires_input), [ginn::SigmoidOp::backward_requires_input](api/Classes/classginn_1_1_sigmoid_op.md#function-backward_requires_input), [ginn::SoftmaxOp::backward_requires_input](api/Classes/classginn_1_1_softmax_op.md#function-backward_requires_input), [ginn::LogOp::backward_requires_input](api/Classes/classginn_1_1_log_op.md#function-backward_requires_input), [ginn::SqrtOp::backward_requires_input](api/Classes/classginn_1_1_sqrt_op.md#function-backward_requires_input), [ginn::Gelu2Op::backward_requires_input](api/Classes/classginn_1_1_gelu2_op.md#function-backward_requires_input), [ginn::GeluOp::backward_requires_input](api/Classes/classginn_1_1_gelu_op.md#function-backward_requires_input)


### function is_identity

```cpp
inline virtual bool is_identity() const
```


### function forward

```cpp
virtual void forward(
    Tensor< Scalar > & ,
    const Tensor< Scalar > & 
) const =0
```


**Reimplemented by**: [ginn::IdentityOp::forward](api/Classes/classginn_1_1_identity_op.md#function-forward), [ginn::TanhOp::forward](api/Classes/classginn_1_1_tanh_op.md#function-forward), [ginn::ReluOp::forward](api/Classes/classginn_1_1_relu_op.md#function-forward), [ginn::SigmoidOp::forward](api/Classes/classginn_1_1_sigmoid_op.md#function-forward), [ginn::SoftmaxOp::forward](api/Classes/classginn_1_1_softmax_op.md#function-forward), [ginn::LogOp::forward](api/Classes/classginn_1_1_log_op.md#function-forward), [ginn::SqrtOp::forward](api/Classes/classginn_1_1_sqrt_op.md#function-forward), [ginn::Gelu2Op::forward](api/Classes/classginn_1_1_gelu2_op.md#function-forward), [ginn::GeluOp::forward](api/Classes/classginn_1_1_gelu_op.md#function-forward)


### function backward

```cpp
virtual void backward(
    Tensor< Scalar > & ,
    const Tensor< Scalar > & ,
    const Tensor< Scalar > & ,
    const Tensor< Scalar > & ,
    bool 
) const =0
```


**Reimplemented by**: [ginn::IdentityOp::backward](api/Classes/classginn_1_1_identity_op.md#function-backward), [ginn::TanhOp::backward](api/Classes/classginn_1_1_tanh_op.md#function-backward), [ginn::ReluOp::backward](api/Classes/classginn_1_1_relu_op.md#function-backward), [ginn::SigmoidOp::backward](api/Classes/classginn_1_1_sigmoid_op.md#function-backward), [ginn::SqrtOp::backward](api/Classes/classginn_1_1_sqrt_op.md#function-backward), [ginn::LogOp::backward](api/Classes/classginn_1_1_log_op.md#function-backward), [ginn::GeluOp::backward](api/Classes/classginn_1_1_gelu_op.md#function-backward), [ginn::SoftmaxOp::backward](api/Classes/classginn_1_1_softmax_op.md#function-backward), [ginn::Gelu2Op::backward](api/Classes/classginn_1_1_gelu2_op.md#function-backward)


### function ~NonlinOp

```cpp
virtual ~NonlinOp() =default
```


### function copy

```cpp
virtual std::unique_ptr< NonlinOp< Scalar > > copy() const =0
```


-------------------------------

Updated on 2022-12-24 at 14:52:49 -0500
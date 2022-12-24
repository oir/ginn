# ginn::Gelu2Op


 [More...](#detailed-description)

Inherits from [ginn::NonlinOp< Scalar >](api/Classes/classginn_1_1_nonlin_op.md)

## Public Functions

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| virtual bool | **[backward_requires_input](api/Classes/classginn_1_1_gelu2_op.md#function-backward_requires_input)**() const override |
| virtual void | **[forward](api/Classes/classginn_1_1_gelu2_op.md#function-forward)**([Tensor](api/Classes/classginn_1_1_tensor.md)< Scalar > & y, const [Tensor](api/Classes/classginn_1_1_tensor.md)< Scalar > & x) const override |
| virtual void | **[backward](api/Classes/classginn_1_1_gelu2_op.md#function-backward)**([Tensor](api/Classes/classginn_1_1_tensor.md)< Scalar > & dx, const [Tensor](api/Classes/classginn_1_1_tensor.md)< Scalar > & dy, const [Tensor](api/Classes/classginn_1_1_tensor.md)< Scalar > & x, const [Tensor](api/Classes/classginn_1_1_tensor.md)< Scalar > & y, bool accumulate) const override |


</span>

## Additional inherited members

</span>

**Public Functions inherited from [ginn::NonlinOp< Scalar >](api/Classes/classginn_1_1_nonlin_op.md)**

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| virtual bool | **[is_identity](api/Classes/classginn_1_1_nonlin_op.md#function-is_identity)**() const |
| virtual | **[~NonlinOp](api/Classes/classginn_1_1_nonlin_op.md#function-~nonlinop)**() =default |
| virtual std::unique_ptr< [NonlinOp](api/Classes/classginn_1_1_nonlin_op.md)< Scalar > > | **[copy](api/Classes/classginn_1_1_nonlin_op.md#function-copy)**() const =0 |


</span>


## Detailed Description

```cpp
template <typename Scalar >
class ginn::Gelu2Op;
```

## Public Functions Documentation

### function backward_requires_input

```cpp
inline virtual bool backward_requires_input() const override
```


**Reimplements**: [ginn::NonlinOp::backward_requires_input](api/Classes/classginn_1_1_nonlin_op.md#function-backward_requires_input)


### function forward

```cpp
inline virtual void forward(
    Tensor< Scalar > & y,
    const Tensor< Scalar > & x
) const override
```


**Reimplements**: [ginn::NonlinOp::forward](api/Classes/classginn_1_1_nonlin_op.md#function-forward)


### function backward

```cpp
inline virtual void backward(
    Tensor< Scalar > & dx,
    const Tensor< Scalar > & dy,
    const Tensor< Scalar > & x,
    const Tensor< Scalar > & y,
    bool accumulate
) const override
```


**Reimplements**: [ginn::NonlinOp::backward](api/Classes/classginn_1_1_nonlin_op.md#function-backward)


-------------------------------

Updated on 2022-12-24 at 15:34:35 -0500
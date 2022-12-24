# ginn::eigen


## Types

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| template <typename Expression \> <br>using TensorRef< [Tensor](api/Classes/classginn_1_1_tensor.md)< typename Eigen::internal::traits< Expression >::Scalar, Eigen::internal::traits< Expression >::NumDimensions, Eigen::internal::traits< Expression >::Layout, typename Eigen::internal::traits< Expression >::Index > > | **[TensorRefLike](api/Namespaces/namespaceginn_1_1eigen.md#using-tensorreflike)**  |
| template <size_t N\> <br>using DSizes< DenseIndex, N > | **[Dims](api/Namespaces/namespaceginn_1_1eigen.md#using-dims)**  |
| template <size_t... Ns\> <br>using IndexList< type2index< Ns >... > | **[Indices](api/Namespaces/namespaceginn_1_1eigen.md#using-indices)**  |


</span>

## Functions

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| template <typename Input ,typename Kernel \> <br>EIGEN_STRONG_INLINE auto | **[Conv2d](api/Namespaces/namespaceginn_1_1eigen.md#function-conv2d)**(const Input & input, const Kernel & kernel, DenseIndex row_stride =1, DenseIndex col_stride =1, PaddingType padding_type =PADDING_SAME, DenseIndex row_in_stride =1, DenseIndex col_in_stride =1) |
| template <typename Input ,typename Kernel ,typename DOutput \> <br>EIGEN_STRONG_INLINE auto | **[Conv2dBackwardKernel](api/Namespaces/namespaceginn_1_1eigen.md#function-conv2dbackwardkernel)**(const Input & input, const Kernel & kernel, const DOutput & d_output, DenseIndex row_stride =1, DenseIndex col_stride =1, PaddingType padding_type =PADDING_SAME, DenseIndex row_in_stride =1, DenseIndex col_in_stride =1) |
| template <typename Input ,typename Kernel ,typename DOutput \> <br>EIGEN_STRONG_INLINE auto | **[Conv2dBackwardInput](api/Namespaces/namespaceginn_1_1eigen.md#function-conv2dbackwardinput)**(const Input & input, const Kernel & kernel, const DOutput & d_output, DenseIndex row_stride =1, DenseIndex col_stride =1, PaddingType  =PADDING_SAME, DenseIndex row_in_stride =1, DenseIndex col_in_stride =1) |
| template <typename Input \> <br>EIGEN_STRONG_INLINE auto | **[MaxPool2d](api/Namespaces/namespaceginn_1_1eigen.md#function-maxpool2d)**(const Input & input, DenseIndex rows, DenseIndex cols, DenseIndex row_stride, DenseIndex col_stride, PaddingType padding_type =PADDING_SAME, DenseIndex row_in_stride =1, DenseIndex col_in_stride =1) |
| template <typename DInput ,typename Input ,typename Output ,typename DOutput \> <br>EIGEN_STRONG_INLINE void | **[MaxPool2dBackwardLoop](api/Namespaces/namespaceginn_1_1eigen.md#function-maxpool2dbackwardloop)**(DInput & d_input, const Input & input, const Output & output, const DOutput & d_output, DenseIndex rows, DenseIndex cols, DenseIndex row_stride, DenseIndex col_stride, DenseIndex row_in_stride =1, DenseIndex col_in_stride =1) |
| template <typename Expression \> <br>constexpr auto | **[ndims](api/Namespaces/namespaceginn_1_1eigen.md#function-ndims)**() |
| template <typename Expression \> <br>auto | **[dsizes](api/Namespaces/namespaceginn_1_1eigen.md#function-dsizes)**(const Expression & expr) |
| template <size_t N,typename Left ,typename Right \> <br>void | **[assign](api/Namespaces/namespaceginn_1_1eigen.md#function-assign)**(Left & left, const Right & right) |
| template <size_t N\> <br>auto | **[as_array](api/Namespaces/namespaceginn_1_1eigen.md#function-as_array)**(const DSizes< DenseIndex, N > & dims) |
| template <typename Expression \> <br>auto | **[dims](api/Namespaces/namespaceginn_1_1eigen.md#function-dims)**(const Expression & expr) |
| template <typename Expression \> <br>auto | **[nelems](api/Namespaces/namespaceginn_1_1eigen.md#function-nelems)**(const Expression & expr) |
| template <typename Expression ,typename... Expressions\> <br>constexpr void | **[static_assert_col_major](api/Namespaces/namespaceginn_1_1eigen.md#function-static_assert_col_major)**() |


</span>

## Types Documentation

### using TensorRefLike

```cpp
template <typename Expression >
using ginn::eigen::TensorRefLike = typedef TensorRef<Tensor<typename Eigen::internal::traits<Expression>::Scalar, Eigen::internal::traits<Expression>::NumDimensions, Eigen::internal::traits<Expression>::Layout, typename Eigen::internal::traits<Expression>::Index> >;
```


### using Dims

```cpp
template <size_t N>
using ginn::eigen::Dims = typedef DSizes<DenseIndex, N>;
```


### using Indices

```cpp
template <size_t... Ns>
using ginn::eigen::Indices = typedef IndexList<type2index<Ns>...>;
```



## Functions Documentation

### function Conv2d

```cpp
template <typename Input ,
typename Kernel >
EIGEN_STRONG_INLINE auto Conv2d(
    const Input & input,
    const Kernel & kernel,
    DenseIndex row_stride =1,
    DenseIndex col_stride =1,
    PaddingType padding_type =PADDING_SAME,
    DenseIndex row_in_stride =1,
    DenseIndex col_in_stride =1
)
```


### function Conv2dBackwardKernel

```cpp
template <typename Input ,
typename Kernel ,
typename DOutput >
EIGEN_STRONG_INLINE auto Conv2dBackwardKernel(
    const Input & input,
    const Kernel & kernel,
    const DOutput & d_output,
    DenseIndex row_stride =1,
    DenseIndex col_stride =1,
    PaddingType padding_type =PADDING_SAME,
    DenseIndex row_in_stride =1,
    DenseIndex col_in_stride =1
)
```


### function Conv2dBackwardInput

```cpp
template <typename Input ,
typename Kernel ,
typename DOutput >
EIGEN_STRONG_INLINE auto Conv2dBackwardInput(
    const Input & input,
    const Kernel & kernel,
    const DOutput & d_output,
    DenseIndex row_stride =1,
    DenseIndex col_stride =1,
    PaddingType  =PADDING_SAME,
    DenseIndex row_in_stride =1,
    DenseIndex col_in_stride =1
)
```


### function MaxPool2d

```cpp
template <typename Input >
EIGEN_STRONG_INLINE auto MaxPool2d(
    const Input & input,
    DenseIndex rows,
    DenseIndex cols,
    DenseIndex row_stride,
    DenseIndex col_stride,
    PaddingType padding_type =PADDING_SAME,
    DenseIndex row_in_stride =1,
    DenseIndex col_in_stride =1
)
```


### function MaxPool2dBackwardLoop

```cpp
template <typename DInput ,
typename Input ,
typename Output ,
typename DOutput >
EIGEN_STRONG_INLINE void MaxPool2dBackwardLoop(
    DInput & d_input,
    const Input & input,
    const Output & output,
    const DOutput & d_output,
    DenseIndex rows,
    DenseIndex cols,
    DenseIndex row_stride,
    DenseIndex col_stride,
    DenseIndex row_in_stride =1,
    DenseIndex col_in_stride =1
)
```


### function ndims

```cpp
template <typename Expression >
constexpr auto ndims()
```


### function dsizes

```cpp
template <typename Expression >
auto dsizes(
    const Expression & expr
)
```


### function assign

```cpp
template <size_t N,
typename Left ,
typename Right >
void assign(
    Left & left,
    const Right & right
)
```


### function as_array

```cpp
template <size_t N>
auto as_array(
    const DSizes< DenseIndex, N > & dims
)
```


### function dims

```cpp
template <typename Expression >
auto dims(
    const Expression & expr
)
```


### function nelems

```cpp
template <typename Expression >
auto nelems(
    const Expression & expr
)
```


### function static_assert_col_major

```cpp
template <typename Expression ,
typename... Expressions>
constexpr void static_assert_col_major()
```






-------------------------------

Updated on 2022-12-24 at 15:34:35 -0500
# ginn::Lstm


 [More...](#detailed-description)

## Public Types

|                | Name           |
| -------------- | -------------- |
| using std::pair< [NodePtr](api/Classes/classginn_1_1_ptr.md)< Scalar >, [NodePtr](api/Classes/classginn_1_1_ptr.md)< Scalar > > | **[State](api/Classes/classginn_1_1_lstm.md#using-state)**  |

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[Lstm](api/Classes/classginn_1_1_lstm.md#function-lstm)**() =default |
| | **[Lstm](api/Classes/classginn_1_1_lstm.md#function-lstm)**(DevPtr dev, Size dim, Size xdim) |
| DevPtr | **[dev](api/Classes/classginn_1_1_lstm.md#function-dev)**() const |
| std::vector< [WeightPtr](api/Classes/classginn_1_1_ptr.md)< Scalar > > | **[weights](api/Classes/classginn_1_1_lstm.md#function-weights)**() |
| void | **[init](api/Classes/classginn_1_1_lstm.md#function-init)**(DevPtr dev, Size dim, Size xdim) |
| void | **[tie](api/Classes/classginn_1_1_lstm.md#function-tie)**([Lstm](api/Classes/classginn_1_1_lstm.md) & other) |
| [Lstm](api/Classes/classginn_1_1_lstm.md) | **[copy](api/Classes/classginn_1_1_lstm.md#function-copy)**(Copy mode) |
| template <typename DataPtrPair \> <br>State | **[step](api/Classes/classginn_1_1_lstm.md#function-step)**(const [NodePtr](api/Classes/classginn_1_1_ptr.md)< Scalar > & x, const DataPtrPair & past) |

## Public Attributes

|                | Name           |
| -------------- | -------------- |
| [WeightPtr](api/Classes/classginn_1_1_ptr.md)< Scalar > | **[Wix](api/Classes/classginn_1_1_lstm.md#variable-wix)**  |
| [WeightPtr](api/Classes/classginn_1_1_ptr.md)< Scalar > | **[Wfx](api/Classes/classginn_1_1_lstm.md#variable-wfx)**  |
| [WeightPtr](api/Classes/classginn_1_1_ptr.md)< Scalar > | **[Wcx](api/Classes/classginn_1_1_lstm.md#variable-wcx)**  |
| [WeightPtr](api/Classes/classginn_1_1_ptr.md)< Scalar > | **[Wox](api/Classes/classginn_1_1_lstm.md#variable-wox)**  |
| [WeightPtr](api/Classes/classginn_1_1_ptr.md)< Scalar > | **[Wih](api/Classes/classginn_1_1_lstm.md#variable-wih)**  |
| [WeightPtr](api/Classes/classginn_1_1_ptr.md)< Scalar > | **[Wfh](api/Classes/classginn_1_1_lstm.md#variable-wfh)**  |
| [WeightPtr](api/Classes/classginn_1_1_ptr.md)< Scalar > | **[Wch](api/Classes/classginn_1_1_lstm.md#variable-wch)**  |
| [WeightPtr](api/Classes/classginn_1_1_ptr.md)< Scalar > | **[Woh](api/Classes/classginn_1_1_lstm.md#variable-woh)**  |
| [WeightPtr](api/Classes/classginn_1_1_ptr.md)< Scalar > | **[Wic](api/Classes/classginn_1_1_lstm.md#variable-wic)**  |
| [WeightPtr](api/Classes/classginn_1_1_ptr.md)< Scalar > | **[Wfc](api/Classes/classginn_1_1_lstm.md#variable-wfc)**  |
| [WeightPtr](api/Classes/classginn_1_1_ptr.md)< Scalar > | **[Woc](api/Classes/classginn_1_1_lstm.md#variable-woc)**  |
| [WeightPtr](api/Classes/classginn_1_1_ptr.md)< Scalar > | **[bi](api/Classes/classginn_1_1_lstm.md#variable-bi)**  |
| [WeightPtr](api/Classes/classginn_1_1_ptr.md)< Scalar > | **[bf](api/Classes/classginn_1_1_lstm.md#variable-bf)**  |
| [WeightPtr](api/Classes/classginn_1_1_ptr.md)< Scalar > | **[bc](api/Classes/classginn_1_1_lstm.md#variable-bc)**  |
| [WeightPtr](api/Classes/classginn_1_1_ptr.md)< Scalar > | **[bo](api/Classes/classginn_1_1_lstm.md#variable-bo)**  |

## Detailed Description

```cpp
template <typename Scalar  =Real>
class ginn::Lstm;
```

## Public Types Documentation

### using State

```cpp
using ginn::Lstm< Scalar >::State =  std::pair<NodePtr<Scalar>, NodePtr<Scalar> >;
```


## Public Functions Documentation

### function Lstm

```cpp
Lstm() =default
```


### function Lstm

```cpp
inline Lstm(
    DevPtr dev,
    Size dim,
    Size xdim
)
```


### function dev

```cpp
inline DevPtr dev() const
```


### function weights

```cpp
inline std::vector< WeightPtr< Scalar > > weights()
```


### function init

```cpp
inline void init(
    DevPtr dev,
    Size dim,
    Size xdim
)
```


### function tie

```cpp
inline void tie(
    Lstm & other
)
```


### function copy

```cpp
inline Lstm copy(
    Copy mode
)
```


### function step

```cpp
template <typename DataPtrPair >
inline State step(
    const NodePtr< Scalar > & x,
    const DataPtrPair & past
)
```


## Public Attributes Documentation

### variable Wix

```cpp
WeightPtr< Scalar > Wix;
```


### variable Wfx

```cpp
WeightPtr< Scalar > Wfx;
```


### variable Wcx

```cpp
WeightPtr< Scalar > Wcx;
```


### variable Wox

```cpp
WeightPtr< Scalar > Wox;
```


### variable Wih

```cpp
WeightPtr< Scalar > Wih;
```


### variable Wfh

```cpp
WeightPtr< Scalar > Wfh;
```


### variable Wch

```cpp
WeightPtr< Scalar > Wch;
```


### variable Woh

```cpp
WeightPtr< Scalar > Woh;
```


### variable Wic

```cpp
WeightPtr< Scalar > Wic;
```


### variable Wfc

```cpp
WeightPtr< Scalar > Wfc;
```


### variable Woc

```cpp
WeightPtr< Scalar > Woc;
```


### variable bi

```cpp
WeightPtr< Scalar > bi;
```


### variable bf

```cpp
WeightPtr< Scalar > bf;
```


### variable bc

```cpp
WeightPtr< Scalar > bc;
```


### variable bo

```cpp
WeightPtr< Scalar > bo;
```


-------------------------------

Updated on 2022-12-24 at 14:52:49 -0500
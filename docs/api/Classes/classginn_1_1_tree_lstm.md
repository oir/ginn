# ginn::TreeLstm


 [More...](#detailed-description)

## Public Types

|                | Name           |
| -------------- | -------------- |
| enum class| **[Reduce](api/Classes/classginn_1_1_tree_lstm.md#enum-reduce)** { add, max} |
| using std::pair< [NodePtr](api/Classes/classginn_1_1_ptr.md)< Scalar >, [NodePtr](api/Classes/classginn_1_1_ptr.md)< Scalar > > | **[State](api/Classes/classginn_1_1_tree_lstm.md#using-state)**  |
| using std::tuple< unsigned, [NodePtr](api/Classes/classginn_1_1_ptr.md)< Scalar >, [NodePtr](api/Classes/classginn_1_1_ptr.md)< Scalar > > | **[Child](api/Classes/classginn_1_1_tree_lstm.md#using-child)**  |

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[TreeLstm](api/Classes/classginn_1_1_tree_lstm.md#function-treelstm)**() =default |
| | **[TreeLstm](api/Classes/classginn_1_1_tree_lstm.md#function-treelstm)**(DevPtr dev, Size labels, Size dim, Size xdim, Reduce reduce =Reduce::add) |
| DevPtr | **[dev](api/Classes/classginn_1_1_tree_lstm.md#function-dev)**() const |
| [TreeLstm](api/Classes/classginn_1_1_tree_lstm.md) | **[copy](api/Classes/classginn_1_1_tree_lstm.md#function-copy)**(Copy mode) |
| | **[TreeLstm](api/Classes/classginn_1_1_tree_lstm.md#function-treelstm)**(const [TreeLstm](api/Classes/classginn_1_1_tree_lstm.md) & l) |
| [TreeLstm](api/Classes/classginn_1_1_tree_lstm.md) & | **[operator=](api/Classes/classginn_1_1_tree_lstm.md#function-operator=)**(const [TreeLstm](api/Classes/classginn_1_1_tree_lstm.md) & ) =default |
| auto | **[weights](api/Classes/classginn_1_1_tree_lstm.md#function-weights)**() |
| void | **[init](api/Classes/classginn_1_1_tree_lstm.md#function-init)**(DevPtr dev, Size a_labels, Size dim, Size xdim, Reduce a_reduce) |
| State | **[step](api/Classes/classginn_1_1_tree_lstm.md#function-step)**(const [NodePtr](api/Classes/classginn_1_1_ptr.md)< Scalar > & x, const std::vector< Child > & children) |

## Public Attributes

|                | Name           |
| -------------- | -------------- |
| Size | **[labels](api/Classes/classginn_1_1_tree_lstm.md#variable-labels)**  |
| Reduce | **[reduce](api/Classes/classginn_1_1_tree_lstm.md#variable-reduce)**  |
| [WeightPtr](api/Classes/classginn_1_1_ptr.md)< Scalar > | **[Wi](api/Classes/classginn_1_1_tree_lstm.md#variable-wi)**  |
| [WeightPtr](api/Classes/classginn_1_1_ptr.md)< Scalar > | **[Wf](api/Classes/classginn_1_1_tree_lstm.md#variable-wf)**  |
| [WeightPtr](api/Classes/classginn_1_1_ptr.md)< Scalar > | **[Wu](api/Classes/classginn_1_1_tree_lstm.md#variable-wu)**  |
| [WeightPtr](api/Classes/classginn_1_1_ptr.md)< Scalar > | **[Wo](api/Classes/classginn_1_1_tree_lstm.md#variable-wo)**  |
| [WeightPtr](api/Classes/classginn_1_1_ptr.md)< Scalar > | **[bi](api/Classes/classginn_1_1_tree_lstm.md#variable-bi)**  |
| [WeightPtr](api/Classes/classginn_1_1_ptr.md)< Scalar > | **[bf](api/Classes/classginn_1_1_tree_lstm.md#variable-bf)**  |
| [WeightPtr](api/Classes/classginn_1_1_ptr.md)< Scalar > | **[bu](api/Classes/classginn_1_1_tree_lstm.md#variable-bu)**  |
| [WeightPtr](api/Classes/classginn_1_1_ptr.md)< Scalar > | **[bo](api/Classes/classginn_1_1_tree_lstm.md#variable-bo)**  |
| std::vector< [WeightPtr](api/Classes/classginn_1_1_ptr.md)< Scalar > > | **[Ui](api/Classes/classginn_1_1_tree_lstm.md#variable-ui)**  |
| std::vector< [WeightPtr](api/Classes/classginn_1_1_ptr.md)< Scalar > > | **[Uu](api/Classes/classginn_1_1_tree_lstm.md#variable-uu)**  |
| std::vector< [WeightPtr](api/Classes/classginn_1_1_ptr.md)< Scalar > > | **[Uo](api/Classes/classginn_1_1_tree_lstm.md#variable-uo)**  |
| std::vector< std::vector< [WeightPtr](api/Classes/classginn_1_1_ptr.md)< Scalar > > > | **[Uf](api/Classes/classginn_1_1_tree_lstm.md#variable-uf)**  |

## Detailed Description

```cpp
template <typename Scalar  =Real>
class ginn::TreeLstm;
```

## Public Types Documentation

### enum Reduce

| Enumerator | Value | Description |
| ---------- | ----- | ----------- |
| add | |   |
| max | |   |




### using State

```cpp
using ginn::TreeLstm< Scalar >::State =  std::pair<NodePtr<Scalar>, NodePtr<Scalar> >;
```


### using Child

```cpp
using ginn::TreeLstm< Scalar >::Child =  std::tuple<unsigned, NodePtr<Scalar>, NodePtr<Scalar> >;
```


## Public Functions Documentation

### function TreeLstm

```cpp
TreeLstm() =default
```


### function TreeLstm

```cpp
inline TreeLstm(
    DevPtr dev,
    Size labels,
    Size dim,
    Size xdim,
    Reduce reduce =Reduce::add
)
```


### function dev

```cpp
inline DevPtr dev() const
```


### function copy

```cpp
inline TreeLstm copy(
    Copy mode
)
```


### function TreeLstm

```cpp
inline TreeLstm(
    const TreeLstm & l
)
```


### function operator=

```cpp
TreeLstm & operator=(
    const TreeLstm & 
) =default
```


### function weights

```cpp
inline auto weights()
```


### function init

```cpp
inline void init(
    DevPtr dev,
    Size a_labels,
    Size dim,
    Size xdim,
    Reduce a_reduce
)
```


### function step

```cpp
inline State step(
    const NodePtr< Scalar > & x,
    const std::vector< Child > & children
)
```


## Public Attributes Documentation

### variable labels

```cpp
Size labels;
```


### variable reduce

```cpp
Reduce reduce = Reduce::add;
```


### variable Wi

```cpp
WeightPtr< Scalar > Wi;
```


### variable Wf

```cpp
WeightPtr< Scalar > Wf;
```


### variable Wu

```cpp
WeightPtr< Scalar > Wu;
```


### variable Wo

```cpp
WeightPtr< Scalar > Wo;
```


### variable bi

```cpp
WeightPtr< Scalar > bi;
```


### variable bf

```cpp
WeightPtr< Scalar > bf;
```


### variable bu

```cpp
WeightPtr< Scalar > bu;
```


### variable bo

```cpp
WeightPtr< Scalar > bo;
```


### variable Ui

```cpp
std::vector< WeightPtr< Scalar > > Ui;
```


### variable Uu

```cpp
std::vector< WeightPtr< Scalar > > Uu;
```


### variable Uo

```cpp
std::vector< WeightPtr< Scalar > > Uo;
```


### variable Uf

```cpp
std::vector< std::vector< WeightPtr< Scalar > > > Uf;
```


-------------------------------

Updated on 2022-12-24 at 14:52:49 -0500
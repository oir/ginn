# ginn::NestedInitListImpl


 [More...](#detailed-description)

## Public Types

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| using std::vector< typename [NestedInitListImpl](api/Classes/structginn_1_1_nested_init_list_impl.md)< Rank - 1, T >::type > | **[type](api/Classes/structginn_1_1_nested_init_list_impl.md#using-type)**  |


</span>

## Detailed Description

```cpp
template <int Rank,
typename T >
struct ginn::NestedInitListImpl;
```

## Public Types Documentation

### using type

```cpp
using ginn::NestedInitListImpl< Rank, T >::type =  std::vector<typename NestedInitListImpl<Rank - 1, T>::type>;
```


-------------------------------

Updated on 2022-12-24 at 15:34:35 -0500
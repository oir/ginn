# ginn::IndexMap


 [More...](#detailed-description)

## Public Functions

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| | **[IndexMap](api/Classes/classginn_1_1_index_map.md#function-indexmap)**() =default |
| template <typename Container \> <br>| **[IndexMap](api/Classes/classginn_1_1_index_map.md#function-indexmap)**(const Container & keys) |
| | **[IndexMap](api/Classes/classginn_1_1_index_map.md#function-indexmap)**(std::initializer_list< Key > keys) |
| void | **[insert](api/Classes/classginn_1_1_index_map.md#function-insert)**(const Key & key) |
| const std::vector< Key > & | **[keys](api/Classes/classginn_1_1_index_map.md#function-keys)**() const |
| bool | **[has](api/Classes/classginn_1_1_index_map.md#function-has)**(const Key & key) const |
| size_t | **[size](api/Classes/classginn_1_1_index_map.md#function-size)**() const |
| void | **[clear](api/Classes/classginn_1_1_index_map.md#function-clear)**() |
| size_t | **[lookup](api/Classes/classginn_1_1_index_map.md#function-lookup)**(const Key & key) const |
| size_t | **[operator[]](api/Classes/classginn_1_1_index_map.md#function-operator[])**(const Key & key) const |
| const Key & | **[reverse_lookup](api/Classes/classginn_1_1_index_map.md#function-reverse_lookup)**(size_t i) const |
| const Key & | **[operator()](api/Classes/classginn_1_1_index_map.md#function-operator())**(size_t i) const |


</span>

## Detailed Description

```cpp
template <typename Key >
class ginn::IndexMap;
```

## Public Functions Documentation

### function IndexMap

```cpp
IndexMap() =default
```


### function IndexMap

```cpp
template <typename Container >
inline IndexMap(
    const Container & keys
)
```


### function IndexMap

```cpp
inline IndexMap(
    std::initializer_list< Key > keys
)
```


### function insert

```cpp
inline void insert(
    const Key & key
)
```


### function keys

```cpp
inline const std::vector< Key > & keys() const
```


### function has

```cpp
inline bool has(
    const Key & key
) const
```


### function size

```cpp
inline size_t size() const
```


### function clear

```cpp
inline void clear()
```


### function lookup

```cpp
inline size_t lookup(
    const Key & key
) const
```


### function operator[]

```cpp
inline size_t operator[](
    const Key & key
) const
```


### function reverse_lookup

```cpp
inline const Key & reverse_lookup(
    size_t i
) const
```


### function operator()

```cpp
inline const Key & operator()(
    size_t i
) const
```


-------------------------------

Updated on 2022-12-24 at 15:34:35 -0500
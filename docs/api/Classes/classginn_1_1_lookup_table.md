# ginn::LookupTable


 [More...](#detailed-description)

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[LookupTable](api/Classes/classginn_1_1_lookup_table.md#function-lookuptable)**(bool has_unk =true) |
| | **[LookupTable](api/Classes/classginn_1_1_lookup_table.md#function-lookuptable)**(const std::unordered_set< Key > & keys, bool has_unk =true) |
| template <typename Function \> <br>| **[LookupTable](api/Classes/classginn_1_1_lookup_table.md#function-lookuptable)**(const std::unordered_set< Key > & keys, Function value_initializer, bool has_unk =true) |
| | **[LookupTable](api/Classes/classginn_1_1_lookup_table.md#function-lookuptable)**(const [LookupTable](api/Classes/classginn_1_1_lookup_table.md) & other) |
| [LookupTable](api/Classes/classginn_1_1_lookup_table.md) & | **[operator=](api/Classes/classginn_1_1_lookup_table.md#function-operator=)**(const [LookupTable](api/Classes/classginn_1_1_lookup_table.md) & other) |
| [LookupTable](api/Classes/classginn_1_1_lookup_table.md) & | **[operator=](api/Classes/classginn_1_1_lookup_table.md#function-operator=)**([LookupTable](api/Classes/classginn_1_1_lookup_table.md) && other) =default |
| NodePtrType & | **[unk](api/Classes/classginn_1_1_lookup_table.md#function-unk)**() |
| [LookupTable](api/Classes/classginn_1_1_lookup_table.md)< Key, NodePtrType > | **[copy](api/Classes/classginn_1_1_lookup_table.md#function-copy)**(Copy mode =Copy::Tied) |
| void | **[tie](api/Classes/classginn_1_1_lookup_table.md#function-tie)**([LookupTable](api/Classes/classginn_1_1_lookup_table.md) & other) |
| std::vector< NodePtrType > | **[weights](api/Classes/classginn_1_1_lookup_table.md#function-weights)**() |
| NodePtrType & | **[operator[]](api/Classes/classginn_1_1_lookup_table.md#function-operator[])**(const Key & key) |
| template <typename Keys \> <br>std::vector< NodePtrType > | **[operator[]](api/Classes/classginn_1_1_lookup_table.md#function-operator[])**(const Keys & keys) |
| void | **[insert](api/Classes/classginn_1_1_lookup_table.md#function-insert)**(const Key & key) |
| void | **[insert](api/Classes/classginn_1_1_lookup_table.md#function-insert)**(const Key & key, const NodePtrType & value) |
| void | **[clear](api/Classes/classginn_1_1_lookup_table.md#function-clear)**() |
| auto | **[size](api/Classes/classginn_1_1_lookup_table.md#function-size)**() const |
| const auto & | **[keys](api/Classes/classginn_1_1_lookup_table.md#function-keys)**() const |

## Detailed Description

```cpp
template <typename Key ,
typename NodePtrType >
class ginn::LookupTable;
```

## Public Functions Documentation

### function LookupTable

```cpp
inline LookupTable(
    bool has_unk =true
)
```


### function LookupTable

```cpp
inline LookupTable(
    const std::unordered_set< Key > & keys,
    bool has_unk =true
)
```


### function LookupTable

```cpp
template <typename Function >
inline LookupTable(
    const std::unordered_set< Key > & keys,
    Function value_initializer,
    bool has_unk =true
)
```


### function LookupTable

```cpp
inline LookupTable(
    const LookupTable & other
)
```


### function operator=

```cpp
inline LookupTable & operator=(
    const LookupTable & other
)
```


### function operator=

```cpp
LookupTable & operator=(
    LookupTable && other
) =default
```


### function unk

```cpp
inline NodePtrType & unk()
```


### function copy

```cpp
inline LookupTable< Key, NodePtrType > copy(
    Copy mode =Copy::Tied
)
```


### function tie

```cpp
inline void tie(
    LookupTable & other
)
```


### function weights

```cpp
inline std::vector< NodePtrType > weights()
```


### function operator[]

```cpp
inline NodePtrType & operator[](
    const Key & key
)
```


### function operator[]

```cpp
template <typename Keys >
inline std::vector< NodePtrType > operator[](
    const Keys & keys
)
```


### function insert

```cpp
inline void insert(
    const Key & key
)
```


### function insert

```cpp
inline void insert(
    const Key & key,
    const NodePtrType & value
)
```


### function clear

```cpp
inline void clear()
```


### function size

```cpp
inline auto size() const
```


### function keys

```cpp
inline const auto & keys() const
```


-------------------------------

Updated on 2022-12-24 at 14:52:49 -0500
# ginn::tree::Tree


 [More...](#detailed-description)

## Public Types

|                | Name           |
| -------------- | -------------- |
| using T | **[value_type](api/Classes/classginn_1_1tree_1_1_tree.md#using-value_type)**  |

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[Tree](api/Classes/classginn_1_1tree_1_1_tree.md#function-tree)**() =default |
| | **[Tree](api/Classes/classginn_1_1tree_1_1_tree.md#function-tree)**(TreeNodePtr< T > a_root) |
| size_t | **[size](api/Classes/classginn_1_1tree_1_1_tree.md#function-size)**() const |
| T & | **[operator[]](api/Classes/classginn_1_1tree_1_1_tree.md#function-operator[])**(size_t t) |
| const T & | **[operator[]](api/Classes/classginn_1_1tree_1_1_tree.md#function-operator[])**(size_t t) const |
| const auto & | **[children_at](api/Classes/classginn_1_1tree_1_1_tree.md#function-children_at)**(size_t t) const |
| auto | **[begin](api/Classes/classginn_1_1tree_1_1_tree.md#function-begin)**() |
| auto | **[end](api/Classes/classginn_1_1tree_1_1_tree.md#function-end)**() |
| auto | **[begin](api/Classes/classginn_1_1tree_1_1_tree.md#function-begin)**() const |
| auto | **[end](api/Classes/classginn_1_1tree_1_1_tree.md#function-end)**() const |

## Public Attributes

|                | Name           |
| -------------- | -------------- |
| TreeNodePtr< T > | **[root](api/Classes/classginn_1_1tree_1_1_tree.md#variable-root)**  |

## Detailed Description

```cpp
template <typename T >
class ginn::tree::Tree;
```

## Public Types Documentation

### using value_type

```cpp
using ginn::tree::Tree< T >::value_type =  T;
```


## Public Functions Documentation

### function Tree

```cpp
Tree() =default
```


### function Tree

```cpp
inline Tree(
    TreeNodePtr< T > a_root
)
```


### function size

```cpp
inline size_t size() const
```


### function operator[]

```cpp
inline T & operator[](
    size_t t
)
```


### function operator[]

```cpp
inline const T & operator[](
    size_t t
) const
```


### function children_at

```cpp
inline const auto & children_at(
    size_t t
) const
```


### function begin

```cpp
inline auto begin()
```


### function end

```cpp
inline auto end()
```


### function begin

```cpp
inline auto begin() const
```


### function end

```cpp
inline auto end() const
```


## Public Attributes Documentation

### variable root

```cpp
TreeNodePtr< T > root;
```


-------------------------------

Updated on 2022-12-24 at 14:52:49 -0500
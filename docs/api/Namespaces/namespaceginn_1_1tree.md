# ginn::tree


## Classes

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| class | **[ginn::tree::DereferencingIterator](api/Classes/classginn_1_1tree_1_1_dereferencing_iterator.md)**  |
| class | **[ginn::tree::Tree](api/Classes/classginn_1_1tree_1_1_tree.md)**  |
| struct | **[ginn::tree::TreeNode](api/Classes/structginn_1_1tree_1_1_tree_node.md)**  |


</span>

## Types

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| template <typename T \> <br>using typename [TreeNode](api/Classes/structginn_1_1tree_1_1_tree_node.md)< T >::TreeNodePtr | **[TreeNodePtr](api/Namespaces/namespaceginn_1_1tree.md#using-treenodeptr)**  |


</span>

## Functions

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| template <typename T \> <br>std::vector< T > | **[sort](api/Namespaces/namespaceginn_1_1tree.md#function-sort)**(const T & root) |
| template <typename T ,typename T2 \> <br>TreeNodePtr< T > | **[make_like](api/Namespaces/namespaceginn_1_1tree.md#function-make_like)**(const T2 & root) |
| template <typename T ,typename T2 \> <br>[Tree](api/Classes/classginn_1_1tree_1_1_tree.md)< T > | **[make_like](api/Namespaces/namespaceginn_1_1tree.md#function-make_like)**(const [Tree](api/Classes/classginn_1_1tree_1_1_tree.md)< T2 > & other) |
| template <typename T ,typename Printer \> <br>void | **[print](api/Namespaces/namespaceginn_1_1tree.md#function-print)**(std::ostream & o, TreeNodePtr< T > n, const Printer & p, bool last_child =true, std::string indent ="") |
| template <typename T ,typename Printer \> <br>void | **[print](api/Namespaces/namespaceginn_1_1tree.md#function-print)**(std::ostream & o, const [Tree](api/Classes/classginn_1_1tree_1_1_tree.md)< T > & t, const Printer & p) |
| template <typename T \> <br>void | **[print](api/Namespaces/namespaceginn_1_1tree.md#function-print)**(std::ostream & out, const [Tree](api/Classes/classginn_1_1tree_1_1_tree.md)< T > & t) |
| template <typename T \> <br>void | **[print](api/Namespaces/namespaceginn_1_1tree.md#function-print)**(const [Tree](api/Classes/classginn_1_1tree_1_1_tree.md)< T > & tree) |
| template <typename T ,typename Reader \> <br>TreeNodePtr< T > | **[parse_helper](api/Namespaces/namespaceginn_1_1tree.md#function-parse_helper)**(std::string_view s, Reader r) |
| template <typename T ,typename Reader \> <br>[Tree](api/Classes/classginn_1_1tree_1_1_tree.md)< T > | **[parse](api/Namespaces/namespaceginn_1_1tree.md#function-parse)**(const std::string & line, Reader r) |
| template <typename T \> <br>[Tree](api/Classes/classginn_1_1tree_1_1_tree.md)< T > | **[parse](api/Namespaces/namespaceginn_1_1tree.md#function-parse)**(const std::string & line) |


</span>

## Types Documentation

### using TreeNodePtr

```cpp
template <typename T >
using ginn::tree::TreeNodePtr = typedef typename TreeNode<T>::TreeNodePtr;
```



## Functions Documentation

### function sort

```cpp
template <typename T >
std::vector< T > sort(
    const T & root
)
```


### function make_like

```cpp
template <typename T ,
typename T2 >
TreeNodePtr< T > make_like(
    const T2 & root
)
```


### function make_like

```cpp
template <typename T ,
typename T2 >
Tree< T > make_like(
    const Tree< T2 > & other
)
```


### function print

```cpp
template <typename T ,
typename Printer >
void print(
    std::ostream & o,
    TreeNodePtr< T > n,
    const Printer & p,
    bool last_child =true,
    std::string indent =""
)
```


### function print

```cpp
template <typename T ,
typename Printer >
void print(
    std::ostream & o,
    const Tree< T > & t,
    const Printer & p
)
```


### function print

```cpp
template <typename T >
void print(
    std::ostream & out,
    const Tree< T > & t
)
```


### function print

```cpp
template <typename T >
void print(
    const Tree< T > & tree
)
```


### function parse_helper

```cpp
template <typename T ,
typename Reader >
TreeNodePtr< T > parse_helper(
    std::string_view s,
    Reader r
)
```


### function parse

```cpp
template <typename T ,
typename Reader >
Tree< T > parse(
    const std::string & line,
    Reader r
)
```


### function parse

```cpp
template <typename T >
Tree< T > parse(
    const std::string & line
)
```






-------------------------------

Updated on 2022-12-24 at 15:34:35 -0500
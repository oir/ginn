# ginn::tree::DereferencingIterator


 [More...](#detailed-description)

## Public Types

|                | Name           |
| -------------- | -------------- |
| using std::forward_iterator_tag | **[iterator_category](api/Classes/classginn_1_1tree_1_1_dereferencing_iterator.md#using-iterator_category)**  |
| using std::ptrdiff_t | **[difference_type](api/Classes/classginn_1_1tree_1_1_dereferencing_iterator.md#using-difference_type)**  |
| using typename std::decay< decltype(*std::declval< typename Iterator::value_type >())>::type | **[value_type](api/Classes/classginn_1_1tree_1_1_dereferencing_iterator.md#using-value_type)**  |
| using value_type * | **[pointer](api/Classes/classginn_1_1tree_1_1_dereferencing_iterator.md#using-pointer)**  |
| using value_type & | **[reference](api/Classes/classginn_1_1tree_1_1_dereferencing_iterator.md#using-reference)**  |

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[DereferencingIterator](api/Classes/classginn_1_1tree_1_1_dereferencing_iterator.md#function-dereferencingiterator)**(pointer p) |
| | **[DereferencingIterator](api/Classes/classginn_1_1tree_1_1_dereferencing_iterator.md#function-dereferencingiterator)**(Iterator it) |
| reference | **[operator*](api/Classes/classginn_1_1tree_1_1_dereferencing_iterator.md#function-operator*)**() const |
| pointer | **[operator->](api/Classes/classginn_1_1tree_1_1_dereferencing_iterator.md#function-operator->)**() |
| auto & | **[operator++](api/Classes/classginn_1_1tree_1_1_dereferencing_iterator.md#function-operator++)**() |
| auto | **[operator++](api/Classes/classginn_1_1tree_1_1_dereferencing_iterator.md#function-operator++)**(int ) |
| bool | **[operator==](api/Classes/classginn_1_1tree_1_1_dereferencing_iterator.md#function-operator==)**(const [DereferencingIterator](api/Classes/classginn_1_1tree_1_1_dereferencing_iterator.md) & other) |
| bool | **[operator!=](api/Classes/classginn_1_1tree_1_1_dereferencing_iterator.md#function-operator!=)**(const [DereferencingIterator](api/Classes/classginn_1_1tree_1_1_dereferencing_iterator.md) & other) |

## Detailed Description

```cpp
template <typename Iterator >
class ginn::tree::DereferencingIterator;
```

## Public Types Documentation

### using iterator_category

```cpp
using ginn::tree::DereferencingIterator< Iterator >::iterator_category =  std::forward_iterator_tag;
```


### using difference_type

```cpp
using ginn::tree::DereferencingIterator< Iterator >::difference_type =  std::ptrdiff_t;
```


### using value_type

```cpp
using ginn::tree::DereferencingIterator< Iterator >::value_type =  typename std::decay< decltype(*std::declval<typename Iterator::value_type>())>::type;
```


### using pointer

```cpp
using ginn::tree::DereferencingIterator< Iterator >::pointer =  value_type*;
```


### using reference

```cpp
using ginn::tree::DereferencingIterator< Iterator >::reference =  value_type&;
```


## Public Functions Documentation

### function DereferencingIterator

```cpp
inline DereferencingIterator(
    pointer p
)
```


### function DereferencingIterator

```cpp
inline DereferencingIterator(
    Iterator it
)
```


### function operator*

```cpp
inline reference operator*() const
```


### function operator->

```cpp
inline pointer operator->()
```


### function operator++

```cpp
inline auto & operator++()
```


### function operator++

```cpp
inline auto operator++(
    int 
)
```


### function operator==

```cpp
inline bool operator==(
    const DereferencingIterator & other
)
```


### function operator!=

```cpp
inline bool operator!=(
    const DereferencingIterator & other
)
```


-------------------------------

Updated on 2022-12-24 at 14:52:49 -0500
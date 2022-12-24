# ginn::Ptr


 [More...](#detailed-description)

## Public Types

|                | Name           |
| -------------- | -------------- |
| using typename std::shared_ptr< NodeType >::element_type | **[element_type](api/Classes/classginn_1_1_ptr.md#using-element_type)**  |

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[Ptr](api/Classes/classginn_1_1_ptr.md#function-ptr)**() =default |
| | **[Ptr](api/Classes/classginn_1_1_ptr.md#function-ptr)**(NodeType * ptr) |
| | **[Ptr](api/Classes/classginn_1_1_ptr.md#function-ptr)**(std::shared_ptr< NodeType > ptr) |
| | **[Ptr](api/Classes/classginn_1_1_ptr.md#function-ptr)**(std::nullptr_t ) |
| template <typename OtherNodeType ,typename  =std::enable_if_t<                std::is_convertible_v<std::shared_ptr<OtherNodeType>,                                      std::shared_ptr<NodeType>>>\> <br>| **[Ptr](api/Classes/classginn_1_1_ptr.md#function-ptr)**(const [Ptr](api/Classes/classginn_1_1_ptr.md)< OtherNodeType > & other) |
| | **[Ptr](api/Classes/classginn_1_1_ptr.md#function-ptr)**(const [Ptr](api/Classes/classginn_1_1_ptr.md)< NodeType > & ) =default |
| [Ptr](api/Classes/classginn_1_1_ptr.md) & | **[operator=](api/Classes/classginn_1_1_ptr.md#function-operator=)**(const [Ptr](api/Classes/classginn_1_1_ptr.md) & ) =default |
| template <typename OtherNodeType \> <br>[Ptr](api/Classes/classginn_1_1_ptr.md) & | **[operator=](api/Classes/classginn_1_1_ptr.md#function-operator=)**(const [Ptr](api/Classes/classginn_1_1_ptr.md)< OtherNodeType > & other) |
| auto | **[operator->](api/Classes/classginn_1_1_ptr.md#function-operator->)**() |
| auto | **[operator->](api/Classes/classginn_1_1_ptr.md#function-operator->)**() const |
| auto & | **[operator*](api/Classes/classginn_1_1_ptr.md#function-operator*)**() |
| const auto & | **[operator*](api/Classes/classginn_1_1_ptr.md#function-operator*)**() const |
| auto | **[get](api/Classes/classginn_1_1_ptr.md#function-get)**() const |
| const auto & | **[as_shared_ptr](api/Classes/classginn_1_1_ptr.md#function-as_shared_ptr)**() const |
| bool | **[operator==](api/Classes/classginn_1_1_ptr.md#function-operator==)**(const [Ptr](api/Classes/classginn_1_1_ptr.md)< NodeType > & other) const |
| | **[operator bool](api/Classes/classginn_1_1_ptr.md#function-operator-bool)**() const |

## Friends

|                | Name           |
| -------------- | -------------- |
| class | **[Ptr](api/Classes/classginn_1_1_ptr.md#friend-ptr)**  |

## Detailed Description

```cpp
template <typename NodeType >
class ginn::Ptr;
```

## Public Types Documentation

### using element_type

```cpp
using ginn::Ptr< NodeType >::element_type =  typename std::shared_ptr<NodeType>::element_type;
```


## Public Functions Documentation

### function Ptr

```cpp
Ptr() =default
```


### function Ptr

```cpp
inline Ptr(
    NodeType * ptr
)
```


### function Ptr

```cpp
inline Ptr(
    std::shared_ptr< NodeType > ptr
)
```


### function Ptr

```cpp
inline Ptr(
    std::nullptr_t 
)
```


### function Ptr

```cpp
template <typename OtherNodeType ,
typename  =std::enable_if_t<                std::is_convertible_v<std::shared_ptr<OtherNodeType>,                                      std::shared_ptr<NodeType>>>>
inline Ptr(
    const Ptr< OtherNodeType > & other
)
```


### function Ptr

```cpp
Ptr(
    const Ptr< NodeType > & 
) =default
```


### function operator=

```cpp
Ptr & operator=(
    const Ptr & 
) =default
```


### function operator=

```cpp
template <typename OtherNodeType >
inline Ptr & operator=(
    const Ptr< OtherNodeType > & other
)
```


### function operator->

```cpp
inline auto operator->()
```


### function operator->

```cpp
inline auto operator->() const
```


### function operator*

```cpp
inline auto & operator*()
```


### function operator*

```cpp
inline const auto & operator*() const
```


### function get

```cpp
inline auto get() const
```


### function as_shared_ptr

```cpp
inline const auto & as_shared_ptr() const
```


### function operator==

```cpp
inline bool operator==(
    const Ptr< NodeType > & other
) const
```


### function operator bool

```cpp
inline explicit operator bool() const
```


## Friends

### friend Ptr

```cpp
friend class Ptr(
    Ptr 
);
```


-------------------------------

Updated on 2022-12-24 at 14:52:49 -0500
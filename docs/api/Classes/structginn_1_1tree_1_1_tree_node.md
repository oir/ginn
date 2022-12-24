# ginn::tree::TreeNode


 [More...](#detailed-description)

## Public Types

|                | Name           |
| -------------- | -------------- |
| using std::shared_ptr< [TreeNode](api/Classes/structginn_1_1tree_1_1_tree_node.md)< T > > | **[TreeNodePtr](api/Classes/structginn_1_1tree_1_1_tree_node.md#using-treenodeptr)**  |
| using std::vector< TreeNodePtr > | **[Children](api/Classes/structginn_1_1tree_1_1_tree_node.md#using-children)**  |

## Public Attributes

|                | Name           |
| -------------- | -------------- |
| T | **[data](api/Classes/structginn_1_1tree_1_1_tree_node.md#variable-data)**  |
| std::vector< TreeNodePtr > | **[children](api/Classes/structginn_1_1tree_1_1_tree_node.md#variable-children)**  |

## Detailed Description

```cpp
template <typename T >
struct ginn::tree::TreeNode;
```

## Public Types Documentation

### using TreeNodePtr

```cpp
using ginn::tree::TreeNode< T >::TreeNodePtr =  std::shared_ptr<TreeNode<T> >;
```


### using Children

```cpp
using ginn::tree::TreeNode< T >::Children =  std::vector<TreeNodePtr>;
```


## Public Attributes Documentation

### variable data

```cpp
T data;
```


### variable children

```cpp
std::vector< TreeNodePtr > children;
```


-------------------------------

Updated on 2022-12-24 at 14:52:49 -0500
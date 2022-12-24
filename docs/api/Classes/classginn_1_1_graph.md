# ginn::Graph




## Public Functions

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| | **[Graph](api/Classes/classginn_1_1_graph.md#function-graph)**([BaseNodePtr](api/Classes/classginn_1_1_ptr.md) e) |
| auto & | **[forward](api/Classes/classginn_1_1_graph.md#function-forward)**() |
| auto & | **[backward](api/Classes/classginn_1_1_graph.md#function-backward)**(double loss_coeff =1) |
| auto & | **[init_grad](api/Classes/classginn_1_1_graph.md#function-init_grad)**() |
| auto & | **[reset_grad](api/Classes/classginn_1_1_graph.md#function-reset_grad)**() |
| auto & | **[reset_forwarded](api/Classes/classginn_1_1_graph.md#function-reset_forwarded)**() |
| const auto & | **[nodes](api/Classes/classginn_1_1_graph.md#function-nodes)**() const |
| [BaseNodePtr](api/Classes/classginn_1_1_ptr.md) | **[sink](api/Classes/classginn_1_1_graph.md#function-sink)**() const |


</span>

## Public Functions Documentation

### function Graph

```cpp
inline Graph(
    BaseNodePtr e
)
```


### function forward

```cpp
inline auto & forward()
```


### function backward

```cpp
inline auto & backward(
    double loss_coeff =1
)
```


### function init_grad

```cpp
inline auto & init_grad()
```


### function reset_grad

```cpp
inline auto & reset_grad()
```


### function reset_forwarded

```cpp
inline auto & reset_forwarded()
```


### function nodes

```cpp
inline const auto & nodes() const
```


### function sink

```cpp
inline BaseNodePtr sink() const
```


-------------------------------

Updated on 2022-12-24 at 15:34:35 -0500
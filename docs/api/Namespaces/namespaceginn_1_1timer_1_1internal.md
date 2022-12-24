# ginn::timer::internal


## Types

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| template <typename Key ,typename Value \> <br>using std::unordered_map< Key, Value > | **[Map](api/Namespaces/namespaceginn_1_1timer_1_1internal.md#using-map)**  |


</span>

## Functions

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| std::string | **[simplify](api/Namespaces/namespaceginn_1_1timer_1_1internal.md#function-simplify)**(Rep micros) |
| std::string | **[make_bar](api/Namespaces/namespaceginn_1_1timer_1_1internal.md#function-make_bar)**(float percent, int width =20) |


</span>

## Attributes

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| Map< std::string, TimePoint > | **[tic_starts](api/Namespaces/namespaceginn_1_1timer_1_1internal.md#variable-tic_starts)**  |
| Map< std::string, Duration > | **[totals](api/Namespaces/namespaceginn_1_1timer_1_1internal.md#variable-totals)**  |
| Map< std::string, unsigned long long > | **[count](api/Namespaces/namespaceginn_1_1timer_1_1internal.md#variable-count)**  |
| TimePoint | **[total_start](api/Namespaces/namespaceginn_1_1timer_1_1internal.md#variable-total_start)**  |
| Duration | **[total](api/Namespaces/namespaceginn_1_1timer_1_1internal.md#variable-total)**  |

## Types Documentation

### using Map

```cpp
template <typename Key ,
typename Value >
using ginn::timer::internal::Map = typedef std::unordered_map<Key, Value>;
```



## Functions Documentation

### function simplify

```cpp
std::string simplify(
    Rep micros
)
```


### function make_bar

```cpp
std::string make_bar(
    float percent,
    int width =20
)
```



## Attributes Documentation

### variable tic_starts

```cpp
Map< std::string, TimePoint > tic_starts;
```


### variable totals

```cpp
Map< std::string, Duration > totals;
```


### variable count

```cpp
Map< std::string, unsigned long long > count;
```


### variable total_start

```cpp
TimePoint total_start;
```


### variable total

```cpp
Duration total;
```





-------------------------------

Updated on 2022-12-24 at 15:34:35 -0500
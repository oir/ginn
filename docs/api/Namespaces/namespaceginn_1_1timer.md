# ginn::timer


## Namespaces

<span class="api-table">

| Name           |
| -------------- |
| **[ginn::timer::internal](api/Namespaces/namespaceginn_1_1timer_1_1internal.md)**  |


</span>

## Types

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| enum| **[Readability](api/Namespaces/namespaceginn_1_1timer.md#enum-readability)** { HumanReadable} |
| enum class| **[TimerSort](api/Namespaces/namespaceginn_1_1timer.md#enum-timersort)** { Duration, Name} |
| using std::chrono::microseconds | **[Duration](api/Namespaces/namespaceginn_1_1timer.md#using-duration)**  |
| using decltype(Duration().count()) | **[Rep](api/Namespaces/namespaceginn_1_1timer.md#using-rep)**  |
| using std::chrono::system_clock | **[Clock](api/Namespaces/namespaceginn_1_1timer.md#using-clock)**  |
| using std::chrono::time_point< Clock > | **[TimePoint](api/Namespaces/namespaceginn_1_1timer.md#using-timepoint)**  |


</span>

## Functions

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| void | **[tic](api/Namespaces/namespaceginn_1_1timer.md#function-tic)**(const std::string & name ="") |
| auto | **[toc](api/Namespaces/namespaceginn_1_1timer.md#function-toc)**(const std::string & name ="") |
| auto | **[get](api/Namespaces/namespaceginn_1_1timer.md#function-get)**(const std::string & name ="") |
| std::string | **[toc](api/Namespaces/namespaceginn_1_1timer.md#function-toc)**(std::string name, Readability ) |
| std::string | **[toc](api/Namespaces/namespaceginn_1_1timer.md#function-toc)**(Readability ) |
| template <typename Duration  =std::chrono::microseconds\> <br>void | **[print](api/Namespaces/namespaceginn_1_1timer.md#function-print)**(TimerSort sort_by =TimerSort::Duration, std::ostream & out =std::cout, bool simple =true) |
| template <typename Duration  =std::chrono::microseconds\> <br>void | **[print](api/Namespaces/namespaceginn_1_1timer.md#function-print)**(std::ostream & out, bool simple =true) |
| void | **[reset](api/Namespaces/namespaceginn_1_1timer.md#function-reset)**() |
| const std::string | **[date_time](api/Namespaces/namespaceginn_1_1timer.md#function-date_time)**(const std::string format ="%Y-%m-%d_%H.%M.%S") |
| template <typename Func \> <br>void | **[time](api/Namespaces/namespaceginn_1_1timer.md#function-time)**(const std::string & name, Func f) |


</span>

## Types Documentation

### enum Readability

| Enumerator | Value | Description |
| ---------- | ----- | ----------- |
| HumanReadable | |   |




### enum TimerSort

| Enumerator | Value | Description |
| ---------- | ----- | ----------- |
| Duration | |   |
| Name | |   |




### using Duration

```cpp
using ginn::timer::Duration = typedef std::chrono::microseconds;
```


### using Rep

```cpp
using ginn::timer::Rep = typedef decltype(Duration().count());
```


### using Clock

```cpp
using ginn::timer::Clock = typedef std::chrono::system_clock;
```


### using TimePoint

```cpp
using ginn::timer::TimePoint = typedef std::chrono::time_point<Clock>;
```



## Functions Documentation

### function tic

```cpp
void tic(
    const std::string & name =""
)
```


### function toc

```cpp
auto toc(
    const std::string & name =""
)
```


### function get

```cpp
auto get(
    const std::string & name =""
)
```


### function toc

```cpp
std::string toc(
    std::string name,
    Readability 
)
```


### function toc

```cpp
std::string toc(
    Readability 
)
```


### function print

```cpp
template <typename Duration  =std::chrono::microseconds>
void print(
    TimerSort sort_by =TimerSort::Duration,
    std::ostream & out =std::cout,
    bool simple =true
)
```


### function print

```cpp
template <typename Duration  =std::chrono::microseconds>
void print(
    std::ostream & out,
    bool simple =true
)
```


### function reset

```cpp
void reset()
```


### function date_time

```cpp
const std::string date_time(
    const std::string format ="%Y-%m-%d_%H.%M.%S"
)
```


### function time

```cpp
template <typename Func >
void time(
    const std::string & name,
    Func f
)
```






-------------------------------

Updated on 2022-12-24 at 15:34:35 -0500
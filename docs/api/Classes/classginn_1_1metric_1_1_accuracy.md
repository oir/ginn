# ginn::metric::Accuracy


 [More...](#detailed-description)

Inherits from [ginn::metric::Metric< T >](api/Classes/classginn_1_1metric_1_1_metric.md)

## Public Functions

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| virtual void | **[add_](api/Classes/classginn_1_1metric_1_1_accuracy.md#function-add_)**(const T & a, const T & b, double weight =1.) override |
| virtual Real | **[eval](api/Classes/classginn_1_1metric_1_1_accuracy.md#function-eval)**() const override |
| virtual void | **[clear](api/Classes/classginn_1_1metric_1_1_accuracy.md#function-clear)**() override |


</span>

## Public Attributes

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| double | **[match](api/Classes/classginn_1_1metric_1_1_accuracy.md#variable-match)**  |
| double | **[count](api/Classes/classginn_1_1metric_1_1_accuracy.md#variable-count)**  |


</span>

## Additional inherited members

</span>

**Public Functions inherited from [ginn::metric::Metric< T >](api/Classes/classginn_1_1metric_1_1_metric.md)**

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| void | **[add](api/Classes/classginn_1_1metric_1_1_metric.md#function-add)**(const LabelType & pred, const LabelType & tru, double weight =1.) |
| template <typename Preds ,typename Trus \> <br>void | **[batched_add](api/Classes/classginn_1_1metric_1_1_metric.md#function-batched_add)**(const Preds & preds, const Trus & trus) |


</span>


## Detailed Description

```cpp
template <typename T >
class ginn::metric::Accuracy;
```

## Public Functions Documentation

### function add_

```cpp
inline virtual void add_(
    const T & a,
    const T & b,
    double weight =1.
) override
```


**Reimplements**: [ginn::metric::Metric::add_](api/Classes/classginn_1_1metric_1_1_metric.md#function-add_)


### function eval

```cpp
inline virtual Real eval() const override
```


**Reimplements**: [ginn::metric::Metric::eval](api/Classes/classginn_1_1metric_1_1_metric.md#function-eval)


### function clear

```cpp
inline virtual void clear() override
```


**Reimplements**: [ginn::metric::Metric::clear](api/Classes/classginn_1_1metric_1_1_metric.md#function-clear)


## Public Attributes Documentation

### variable match

```cpp
double match = 0;
```


### variable count

```cpp
double count = 0;
```


-------------------------------

Updated on 2022-12-24 at 15:34:35 -0500
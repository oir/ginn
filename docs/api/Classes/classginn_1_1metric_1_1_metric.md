# ginn::metric::Metric


 [More...](#detailed-description)

## Public Functions

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| void | **[add](api/Classes/classginn_1_1metric_1_1_metric.md#function-add)**(const LabelType & pred, const LabelType & tru, double weight =1.) |
| template <typename Preds ,typename Trus \> <br>void | **[batched_add](api/Classes/classginn_1_1metric_1_1_metric.md#function-batched_add)**(const Preds & preds, const Trus & trus) |
| virtual Real | **[eval](api/Classes/classginn_1_1metric_1_1_metric.md#function-eval)**() const =0 |
| virtual void | **[clear](api/Classes/classginn_1_1metric_1_1_metric.md#function-clear)**() =0 |


</span>

## Detailed Description

```cpp
template <typename LabelType >
class ginn::metric::Metric;
```

## Public Functions Documentation

### function add

```cpp
inline void add(
    const LabelType & pred,
    const LabelType & tru,
    double weight =1.
)
```


### function batched_add

```cpp
template <typename Preds ,
typename Trus >
inline void batched_add(
    const Preds & preds,
    const Trus & trus
)
```


### function eval

```cpp
virtual Real eval() const =0
```


**Reimplemented by**: [ginn::metric::Accuracy::eval](api/Classes/classginn_1_1metric_1_1_accuracy.md#function-eval), [ginn::metric::MSE::eval](api/Classes/classginn_1_1metric_1_1_m_s_e.md#function-eval), [ginn::metric::F1::eval](api/Classes/classginn_1_1metric_1_1_f1.md#function-eval), [ginn::metric::SpanF1::eval](api/Classes/classginn_1_1metric_1_1_span_f1.md#function-eval)


### function clear

```cpp
virtual void clear() =0
```


**Reimplemented by**: [ginn::metric::Accuracy::clear](api/Classes/classginn_1_1metric_1_1_accuracy.md#function-clear), [ginn::metric::MSE::clear](api/Classes/classginn_1_1metric_1_1_m_s_e.md#function-clear), [ginn::metric::F1::clear](api/Classes/classginn_1_1metric_1_1_f1.md#function-clear), [ginn::metric::SpanF1::clear](api/Classes/classginn_1_1metric_1_1_span_f1.md#function-clear)


-------------------------------

Updated on 2022-12-24 at 15:34:35 -0500
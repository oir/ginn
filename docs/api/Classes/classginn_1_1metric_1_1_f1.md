# ginn::metric::F1


 [More...](#detailed-description)

Inherits from [ginn::metric::Metric< Label >](api/Classes/classginn_1_1metric_1_1_metric.md)

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[F1](api/Classes/classginn_1_1metric_1_1_f1.md#function-f1)**(const Label & a_all, const Label & a_macro) |
| virtual void | **[add_](api/Classes/classginn_1_1metric_1_1_f1.md#function-add_)**(const Label & pred, const Label & tru, double weight =1.) |
| std::map< Label, [F1Value](api/Classes/structginn_1_1metric_1_1_f1_value.md) > | **[eval_all](api/Classes/classginn_1_1metric_1_1_f1.md#function-eval_all)**() const |
| virtual Real | **[eval](api/Classes/classginn_1_1metric_1_1_f1.md#function-eval)**() const override |
| virtual void | **[clear](api/Classes/classginn_1_1metric_1_1_f1.md#function-clear)**() override |

## Public Attributes

|                | Name           |
| -------------- | -------------- |
| const Label | **[all](api/Classes/classginn_1_1metric_1_1_f1.md#variable-all)**  |
| const Label | **[macro](api/Classes/classginn_1_1metric_1_1_f1.md#variable-macro)**  |
| std::unordered_set< Label > | **[tags](api/Classes/classginn_1_1metric_1_1_f1.md#variable-tags)**  |
| std::unordered_map< Label, double > | **[pred_counts](api/Classes/classginn_1_1metric_1_1_f1.md#variable-pred_counts)**  |
| std::unordered_map< Label, double > | **[tru_counts](api/Classes/classginn_1_1metric_1_1_f1.md#variable-tru_counts)**  |
| std::unordered_map< Label, double > | **[match_counts](api/Classes/classginn_1_1metric_1_1_f1.md#variable-match_counts)**  |

## Additional inherited members

**Public Functions inherited from [ginn::metric::Metric< Label >](api/Classes/classginn_1_1metric_1_1_metric.md)**

|                | Name           |
| -------------- | -------------- |
| void | **[add](api/Classes/classginn_1_1metric_1_1_metric.md#function-add)**(const LabelType & pred, const LabelType & tru, double weight =1.) |
| template <typename Preds ,typename Trus \> <br>void | **[batched_add](api/Classes/classginn_1_1metric_1_1_metric.md#function-batched_add)**(const Preds & preds, const Trus & trus) |


## Detailed Description

```cpp
template <typename Label >
class ginn::metric::F1;
```

## Public Functions Documentation

### function F1

```cpp
inline F1(
    const Label & a_all,
    const Label & a_macro
)
```


### function add_

```cpp
inline virtual void add_(
    const Label & pred,
    const Label & tru,
    double weight =1.
)
```


**Reimplements**: [ginn::metric::Metric::add_](api/Classes/classginn_1_1metric_1_1_metric.md#function-add_)


### function eval_all

```cpp
inline std::map< Label, F1Value > eval_all() const
```


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

### variable all

```cpp
const Label all;
```


### variable macro

```cpp
const Label macro;
```


### variable tags

```cpp
std::unordered_set< Label > tags {all};
```


### variable pred_counts

```cpp
std::unordered_map< Label, double > pred_counts;
```


### variable tru_counts

```cpp
std::unordered_map< Label, double > tru_counts;
```


### variable match_counts

```cpp
std::unordered_map< Label, double > match_counts;
```


-------------------------------

Updated on 2022-12-24 at 14:52:49 -0500
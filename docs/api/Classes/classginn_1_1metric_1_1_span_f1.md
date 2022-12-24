# ginn::metric::SpanF1




Inherits from [ginn::metric::Metric< std::vector< std::string > >](api/Classes/classginn_1_1metric_1_1_metric.md)

## Public Types

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| typedef std::pair< Real, Real > | **[Span](api/Classes/classginn_1_1metric_1_1_span_f1.md#typedef-span)**  |


</span>

## Public Functions

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| virtual void | **[add_](api/Classes/classginn_1_1metric_1_1_span_f1.md#function-add_)**(const std::vector< std::string > & pred, const std::vector< std::string > & tru, double  =1.) override |
| std::unordered_map< std::string, [F1Value](api/Classes/structginn_1_1metric_1_1_f1_value.md) > | **[eval_all](api/Classes/classginn_1_1metric_1_1_span_f1.md#function-eval_all)**() const |
| virtual Real | **[eval](api/Classes/classginn_1_1metric_1_1_span_f1.md#function-eval)**() const override |
| virtual void | **[clear](api/Classes/classginn_1_1metric_1_1_span_f1.md#function-clear)**() override |


</span>

## Public Attributes

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| const std::string | **[all](api/Classes/classginn_1_1metric_1_1_span_f1.md#variable-all)**  |
| std::unordered_set< std::string > | **[tags](api/Classes/classginn_1_1metric_1_1_span_f1.md#variable-tags)**  |
| std::unordered_map< std::string, size_t > | **[pred_counts](api/Classes/classginn_1_1metric_1_1_span_f1.md#variable-pred_counts)**  |
| std::unordered_map< std::string, size_t > | **[tru_counts](api/Classes/classginn_1_1metric_1_1_span_f1.md#variable-tru_counts)**  |
| std::unordered_map< std::string, size_t > | **[match_counts](api/Classes/classginn_1_1metric_1_1_span_f1.md#variable-match_counts)**  |


</span>

## Additional inherited members

</span>

**Public Functions inherited from [ginn::metric::Metric< std::vector< std::string > >](api/Classes/classginn_1_1metric_1_1_metric.md)**

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| void | **[add](api/Classes/classginn_1_1metric_1_1_metric.md#function-add)**(const LabelType & pred, const LabelType & tru, double weight =1.) |
| template <typename Preds ,typename Trus \> <br>void | **[batched_add](api/Classes/classginn_1_1metric_1_1_metric.md#function-batched_add)**(const Preds & preds, const Trus & trus) |


</span>


## Public Types Documentation

### typedef Span

```cpp
typedef std::pair<Real, Real> ginn::metric::SpanF1::Span;
```


## Public Functions Documentation

### function add_

```cpp
inline virtual void add_(
    const std::vector< std::string > & pred,
    const std::vector< std::string > & tru,
    double  =1.
) override
```


**Reimplements**: [ginn::metric::Metric::add_](api/Classes/classginn_1_1metric_1_1_metric.md#function-add_)


### function eval_all

```cpp
inline std::unordered_map< std::string, F1Value > eval_all() const
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
const std::string all = "all";
```


### variable tags

```cpp
std::unordered_set< std::string > tags {all};
```


### variable pred_counts

```cpp
std::unordered_map< std::string, size_t > pred_counts;
```


### variable tru_counts

```cpp
std::unordered_map< std::string, size_t > tru_counts;
```


### variable match_counts

```cpp
std::unordered_map< std::string, size_t > match_counts;
```


-------------------------------

Updated on 2022-12-24 at 15:34:35 -0500
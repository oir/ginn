# ginn::AliasSampler


 [More...](#detailed-description)


`#include <sample.h>`

## Public Types

|                | Name           |
| -------------- | -------------- |
| using size_t | **[Index](api/Classes/classginn_1_1_alias_sampler.md#using-index)**  |

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[AliasSampler](api/Classes/classginn_1_1_alias_sampler.md#function-aliassampler)**(const std::vector< double > & probs) |
| void | **[set_seed](api/Classes/classginn_1_1_alias_sampler.md#function-set_seed)**(unsigned seed) |
| Index | **[sample](api/Classes/classginn_1_1_alias_sampler.md#function-sample)**() |
| size_t | **[num_classes](api/Classes/classginn_1_1_alias_sampler.md#function-num_classes)**() |
| Index | **[operator()](api/Classes/classginn_1_1_alias_sampler.md#function-operator())**() |

## Detailed Description

```cpp
class ginn::AliasSampler;
```


Algorithm to sample from a fixed categorical distribution in constant time. Implements Vose's Alias Method as described in: [https://www.keithschwarz.com/darts-dice-coins/](https://www.keithschwarz.com/darts-dice-coins/)

## Public Types Documentation

### using Index

```cpp
using ginn::AliasSampler::Index =  size_t;
```


## Public Functions Documentation

### function AliasSampler

```cpp
inline AliasSampler(
    const std::vector< double > & probs
)
```


### function set_seed

```cpp
inline void set_seed(
    unsigned seed
)
```


### function sample

```cpp
inline Index sample()
```


### function num_classes

```cpp
inline size_t num_classes()
```


### function operator()

```cpp
inline Index operator()()
```


-------------------------------

Updated on 2022-12-24 at 14:52:49 -0500
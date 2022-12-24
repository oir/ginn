# ginn::util


## Functions

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| template <typename Scalar \> <br>void | **[load_wvecs](api/Namespaces/namespaceginn_1_1util.md#function-load_wvecs)**([LookupTable](api/Classes/classginn_1_1_lookup_table.md)< std::string, [WeightPtr](api/Classes/classginn_1_1_ptr.md)< Scalar > > & table, DevPtr dev, const std::string & fname, const std::unordered_set< std::string > & vocab, bool fixed =false, size_t max =std::numeric_limits< size_t >::max()) |


</span>


## Functions Documentation

### function load_wvecs

```cpp
template <typename Scalar >
void load_wvecs(
    LookupTable< std::string, WeightPtr< Scalar > > & table,
    DevPtr dev,
    const std::string & fname,
    const std::unordered_set< std::string > & vocab,
    bool fixed =false,
    size_t max =std::numeric_limits< size_t >::max()
)
```






-------------------------------

Updated on 2022-12-24 at 15:34:35 -0500
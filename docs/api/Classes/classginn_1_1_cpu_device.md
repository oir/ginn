# ginn::CpuDevice




Inherits from [ginn::Device](api/Classes/classginn_1_1_device.md)

## Public Functions

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| virtual void * | **[alloc](api/Classes/classginn_1_1_cpu_device.md#function-alloc)**(size_t size) override |
| virtual void * | **[realloc](api/Classes/classginn_1_1_cpu_device.md#function-realloc)**(void * data, size_t size) override |
| virtual void | **[free](api/Classes/classginn_1_1_cpu_device.md#function-free)**(void * data) override |
| virtual DeviceKind | **[kind](api/Classes/classginn_1_1_cpu_device.md#function-kind)**() const override |
| virtual [DeviceId](api/Classes/structginn_1_1_device_id.md) | **[id](api/Classes/classginn_1_1_cpu_device.md#function-id)**() const override |


</span>

## Additional inherited members

</span>

**Public Functions inherited from [ginn::Device](api/Classes/classginn_1_1_device.md)**

<span class="api-table">

|                | Name           |
| -------------- | -------------- |
| virtual short | **[precedence](api/Classes/classginn_1_1_device.md#function-precedence)**() const |
| void | **[copy](api/Classes/classginn_1_1_device.md#function-copy)**(const [Device](api/Classes/classginn_1_1_device.md) & other, void * data, void * other_data, size_t size) |
| virtual | **[~Device](api/Classes/classginn_1_1_device.md#function-~device)**() =default |


</span>


## Public Functions Documentation

### function alloc

```cpp
inline virtual void * alloc(
    size_t size
) override
```


**Reimplements**: [ginn::Device::alloc](api/Classes/classginn_1_1_device.md#function-alloc)


### function realloc

```cpp
inline virtual void * realloc(
    void * data,
    size_t size
) override
```


**Reimplements**: [ginn::Device::realloc](api/Classes/classginn_1_1_device.md#function-realloc)


### function free

```cpp
inline virtual void free(
    void * data
) override
```


**Reimplements**: [ginn::Device::free](api/Classes/classginn_1_1_device.md#function-free)


### function kind

```cpp
inline virtual DeviceKind kind() const override
```


**Reimplements**: [ginn::Device::kind](api/Classes/classginn_1_1_device.md#function-kind)


### function id

```cpp
inline virtual DeviceId id() const override
```


**Reimplements**: [ginn::Device::id](api/Classes/classginn_1_1_device.md#function-id)


-------------------------------

Updated on 2022-12-24 at 15:34:35 -0500
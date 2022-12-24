# ginn::Device




Inherited by [ginn::CpuDevice](api/Classes/classginn_1_1_cpu_device.md), [ginn::NullDevice](api/Classes/classginn_1_1_null_device.md), [ginn::PreallocCpuDevice](api/Classes/classginn_1_1_prealloc_cpu_device.md)

## Public Functions

|                | Name           |
| -------------- | -------------- |
| virtual void * | **[alloc](api/Classes/classginn_1_1_device.md#function-alloc)**(size_t size) =0 |
| virtual void * | **[realloc](api/Classes/classginn_1_1_device.md#function-realloc)**(void * data, size_t size) =0 |
| virtual void | **[free](api/Classes/classginn_1_1_device.md#function-free)**(void * data) =0 |
| virtual DeviceKind | **[kind](api/Classes/classginn_1_1_device.md#function-kind)**() const =0 |
| virtual [DeviceId](api/Classes/structginn_1_1_device_id.md) | **[id](api/Classes/classginn_1_1_device.md#function-id)**() const =0 |
| virtual short | **[precedence](api/Classes/classginn_1_1_device.md#function-precedence)**() const |
| void | **[copy](api/Classes/classginn_1_1_device.md#function-copy)**(const [Device](api/Classes/classginn_1_1_device.md) & other, void * data, void * other_data, size_t size) |
| virtual | **[~Device](api/Classes/classginn_1_1_device.md#function-~device)**() =default |

## Public Functions Documentation

### function alloc

```cpp
virtual void * alloc(
    size_t size
) =0
```


**Reimplemented by**: [ginn::CpuDevice::alloc](api/Classes/classginn_1_1_cpu_device.md#function-alloc), [ginn::PreallocCpuDevice::alloc](api/Classes/classginn_1_1_prealloc_cpu_device.md#function-alloc), [ginn::NullDevice::alloc](api/Classes/classginn_1_1_null_device.md#function-alloc)


### function realloc

```cpp
virtual void * realloc(
    void * data,
    size_t size
) =0
```


**Reimplemented by**: [ginn::NullDevice::realloc](api/Classes/classginn_1_1_null_device.md#function-realloc), [ginn::PreallocCpuDevice::realloc](api/Classes/classginn_1_1_prealloc_cpu_device.md#function-realloc), [ginn::CpuDevice::realloc](api/Classes/classginn_1_1_cpu_device.md#function-realloc)


### function free

```cpp
virtual void free(
    void * data
) =0
```


**Reimplemented by**: [ginn::NullDevice::free](api/Classes/classginn_1_1_null_device.md#function-free), [ginn::PreallocCpuDevice::free](api/Classes/classginn_1_1_prealloc_cpu_device.md#function-free), [ginn::CpuDevice::free](api/Classes/classginn_1_1_cpu_device.md#function-free)


### function kind

```cpp
virtual DeviceKind kind() const =0
```


**Reimplemented by**: [ginn::NullDevice::kind](api/Classes/classginn_1_1_null_device.md#function-kind), [ginn::CpuDevice::kind](api/Classes/classginn_1_1_cpu_device.md#function-kind), [ginn::PreallocCpuDevice::kind](api/Classes/classginn_1_1_prealloc_cpu_device.md#function-kind)


### function id

```cpp
virtual DeviceId id() const =0
```


**Reimplemented by**: [ginn::NullDevice::id](api/Classes/classginn_1_1_null_device.md#function-id), [ginn::CpuDevice::id](api/Classes/classginn_1_1_cpu_device.md#function-id), [ginn::PreallocCpuDevice::id](api/Classes/classginn_1_1_prealloc_cpu_device.md#function-id)


### function precedence

```cpp
inline virtual short precedence() const
```


**Reimplemented by**: [ginn::NullDevice::precedence](api/Classes/classginn_1_1_null_device.md#function-precedence), [ginn::PreallocCpuDevice::precedence](api/Classes/classginn_1_1_prealloc_cpu_device.md#function-precedence)


### function copy

```cpp
inline void copy(
    const Device & other,
    void * data,
    void * other_data,
    size_t size
)
```


### function ~Device

```cpp
virtual ~Device() =default
```


-------------------------------

Updated on 2022-12-24 at 14:52:49 -0500
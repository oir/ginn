# ginn::NullDevice




Inherits from [ginn::Device](api/Classes/classginn_1_1_device.md)

## Public Functions

|                | Name           |
| -------------- | -------------- |
| virtual void * | **[alloc](api/Classes/classginn_1_1_null_device.md#function-alloc)**(size_t ) override |
| virtual void * | **[realloc](api/Classes/classginn_1_1_null_device.md#function-realloc)**(void * , size_t ) override |
| virtual void | **[free](api/Classes/classginn_1_1_null_device.md#function-free)**(void * ) override |
| virtual DeviceKind | **[kind](api/Classes/classginn_1_1_null_device.md#function-kind)**() const override |
| virtual [DeviceId](api/Classes/structginn_1_1_device_id.md) | **[id](api/Classes/classginn_1_1_null_device.md#function-id)**() const override |
| virtual short | **[precedence](api/Classes/classginn_1_1_null_device.md#function-precedence)**() const override |

## Additional inherited members

**Public Functions inherited from [ginn::Device](api/Classes/classginn_1_1_device.md)**

|                | Name           |
| -------------- | -------------- |
| void | **[copy](api/Classes/classginn_1_1_device.md#function-copy)**(const [Device](api/Classes/classginn_1_1_device.md) & other, void * data, void * other_data, size_t size) |
| virtual | **[~Device](api/Classes/classginn_1_1_device.md#function-~device)**() =default |


## Public Functions Documentation

### function alloc

```cpp
inline virtual void * alloc(
    size_t 
) override
```


**Reimplements**: [ginn::Device::alloc](api/Classes/classginn_1_1_device.md#function-alloc)


### function realloc

```cpp
inline virtual void * realloc(
    void * ,
    size_t 
) override
```


**Reimplements**: [ginn::Device::realloc](api/Classes/classginn_1_1_device.md#function-realloc)


### function free

```cpp
inline virtual void free(
    void * 
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


### function precedence

```cpp
inline virtual short precedence() const override
```


**Reimplements**: [ginn::Device::precedence](api/Classes/classginn_1_1_device.md#function-precedence)


-------------------------------

Updated on 2022-12-24 at 14:52:49 -0500
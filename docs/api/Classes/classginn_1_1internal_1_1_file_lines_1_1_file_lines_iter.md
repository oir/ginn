# ginn::internal::FileLines::FileLinesIter




## Public Functions

|                | Name           |
| -------------- | -------------- |
| const std::string & | **[operator*](api/Classes/classginn_1_1internal_1_1_file_lines_1_1_file_lines_iter.md#function-operator*)**() const |
| bool | **[operator!=](api/Classes/classginn_1_1internal_1_1_file_lines_1_1_file_lines_iter.md#function-operator!=)**(const [FileLinesIter](api/Classes/classginn_1_1internal_1_1_file_lines_1_1_file_lines_iter.md) & right) const |
| [FileLinesIter](api/Classes/classginn_1_1internal_1_1_file_lines_1_1_file_lines_iter.md) & | **[operator++](api/Classes/classginn_1_1internal_1_1_file_lines_1_1_file_lines_iter.md#function-operator++)**() |
| | **[FileLinesIter](api/Classes/classginn_1_1internal_1_1_file_lines_1_1_file_lines_iter.md#function-filelinesiter)**(std::ifstream & in, bool eof =false) |

## Public Functions Documentation

### function operator*

```cpp
inline const std::string & operator*() const
```


### function operator!=

```cpp
inline bool operator!=(
    const FileLinesIter & right
) const
```


### function operator++

```cpp
inline FileLinesIter & operator++()
```


### function FileLinesIter

```cpp
inline FileLinesIter(
    std::ifstream & in,
    bool eof =false
)
```


-------------------------------

Updated on 2022-12-24 at 14:52:49 -0500
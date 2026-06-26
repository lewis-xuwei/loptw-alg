# 1 Dependencies

## 1.1 Install conan dependency manager

```shell
pip install conan
```

## 1.2 Using conan to install dependencies

```shell
conan install . -s build_type=Debug --build=missing
# conan install . -s build_type=Release --build=missing
```

# 2 Compilation

```shell
cmake --preset conan-default
cd ./build/
cmake --build .
```


# 3 Unit test

```shell
ctest -C Debug
```

# 📦 SCALE codec C++ implementation

This Conan package builds and packages the scale-codec-cpp library.
The library was slightly modified to make the build working as static library. Check [qdrvm/scale-codec-cpp](https://github.com/qdrvm/scale-codec-cpp) for further instructions.

## Requirements

- Conan
- CMake
- A C++ compiler

## 🚀 Usage

Add this package to your project's `conanfile.txt`:

```ini
[requires]
libscale/1.1.0@svnscha/dev

[generators]
cmake
```

To install dependencies, run:

```sh
conan install .
```

To build your project with Conan, run:

```sh
mkdir build && cd build
conan build ..
```

## 🧪 Building the Package

To create the Conan package, navigate to the directory containing conanfile.py and run:

```sh
conan create --user svnscha --channel dev -s build_type=Debug .
conan create --user svnscha --channel dev -s build_type=Release .
```

For local development you could simply use

```sh
conan create .
```

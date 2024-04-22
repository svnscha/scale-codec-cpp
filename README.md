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
libscale/1.1.1@svnscha/dev

[generators]
cmake
```

## 🧪 Export the Package

To export the Conan package, navigate to the directory containing conanfile.py and run:

```sh
conan export --user svnscha --channel dev .
```

This exports the package to your local cache, usable by other projects.

## 🧪 Building the Package

For local development you could simply use

```sh
conan create .
```

or similar.

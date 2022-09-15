# 👽 🔫 🗿
## space shooter 1000


## Building

### Prerequisites
- Install Conan with ```pip install conan``` on Windows or ```brew install conan``` on macOS
- Install Cmake from [here](https://cmake.org/download/) if you are on Windows. Ensure Cmake is added to PATH. 
    - If you are using MacOS, install with ```brew install cmake```

### Setting up Conan

If you haven't already, set up a Conan profile.

```sh
conan profile new default --detect
```

### Installing dependencies

```sh
mkdir build
cd build
conan install .. --build=missing 
```

### Running the build

```sh
cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake
cmake --build build --config Release
```

On Windows, you might have to instead try

```sh
cmake -S . -B build -G "Visual Studio 15 2017" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake
```

if using Visual Studio 15 2017 for example, and it matches your default profile, or you can use "Unix Makefiles" for linux and mac as an alternative. More information [here](https://docs.conan.io/en/1.7/getting_started.html).

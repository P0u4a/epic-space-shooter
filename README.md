# 👽 🔫 🗿
## space shooter 1000


## Building

### Prerequisites
- Install Conan with ```pip install conan```. Mac users can also use ```brew install conan```.
- Install Cmake from [here](https://cmake.org/download/), ensuring Cmake is added to PATH. 
  If you are using macOS, you can also install with ```brew install cmake```.

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

If you're building for MacOS, you'll have to copy the `.dylib` files generated in `build/bin` over to `/usr/local/lib`.

### Running the build

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

If you're building for MacOS, you'll have to add a couple of extra flags when building relevant to your system:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DMACOS=true -DARM=true
```
Where `-DMACOS` sets up CMake to build for Mac, and `-DARM` is needed if you're using Apple silicon.

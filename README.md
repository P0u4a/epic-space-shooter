# Epic Space Shooter 👾
A two player space shooter, built entirely in C++, using SFML.
## Game Controls
|          | Accelerate | Rotate Right | Rotate Left | Shoot      | Pause Game |
|----------|------------|--------------|-------------|------------|------------|
| Player 1 | W          | A            | S           | D          | Escape     |
| Player 2 | Up Arrow   | Right Arrow  | Left Arrow  | Down Arrow | Escape     |

## Preview
![Screenshot (28)](https://user-images.githubusercontent.com/66873325/196380572-f2cbc968-ecb8-47b1-9336-1b60680ba234.png)
![Screenshot (27)](https://user-images.githubusercontent.com/66873325/196380533-66618c70-f796-4504-9b09-b91335ed9e85.png)

## Building

### Prerequisites
- Install Conan with ```pip install conan```. Mac users can also use ```brew install conan```.
- Install Cmake from [here](https://cmake.org/download/), ensuring Cmake is added to PATH. 
  If you are using macOS, you can also install with ```brew install cmake```.
- Linting requires Python, clang-format, clang-tidy, and [include-what-you-use](https://include-what-you-use.org/) to be installed and added to PATH.

### Setting up Conan

If you haven't already, set up a Conan profile.

```sh
conan profile new default --detect
```

You might also need to set your conan profile to use the libcxx c++11 abi and to use the c++ 17 std:

```sh
conan profile update settings.compiler.libcxx=libstdc++11 default
conan profile update settings.cppstd=17 default
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

Building for release will include a linting pass, which requires clang-format, clang-tidy, include-what-you-use, and Python to be available in PATH.

If you're building for MacOS, you'll have to add a couple of extra flags when building relevant to your system:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DMACOS=TRUE -DARM=TRUE
```
Where `-DMACOS` sets up CMake to build for Mac, and `-DARM` is needed if you're using Apple silicon.

### Testing

To build tests, pass the `-DTEST=1` flag to cmake:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DTEST=1 ...
cmake --build build --config Release
```

Then to run the tests:

```sh
./build/bin/tests
```

cmake_minimum_required(VERSION 3.11)

project(Epic-Space-Shooter
        VERSION 1.0
        DESCRIPTION "OOP Group project"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(-Wall -Wextra -Wpedantic)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS src/*.cpp src/*.h)

add_executable(epic-space-shooter ${SOURCE_FILES})


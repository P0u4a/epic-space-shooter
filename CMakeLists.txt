cmake_minimum_required(VERSION 3.11)

if(NOT MACOS)
    list(APPEND LANGUAGES CXX)
else()
    # Macos specific rules. For more information on how these rules were
    # selected, see: https://github.com/GAIGResearch/Stratega/issues/108,
    # https://stratega.readthedocs.io/en/latest/gettingStarted/installation/index.html,
    # https://github.com/bincrafters/community/issues/534
    message("Building for MACOS")
    list(APPEND LANGUAGES C CXX OBJC OBJCXX)
    enable_language(OBJC)
    enable_language(OBJCXX)
    set(CMAKE_CXX_COMPILER_VERSION 13.0)

    if(ARM)
        message("Building for ARM")
        set(CMAKE_OSX_ARCHITECTURES "arm64")
        option(BUILD_SHARED_LIBS "Enable compilation of shared libraries" ON)
        option(SGA_BUILD_SFML_FROM_SOURCE "Compile SFML 2.6.x" ON)
    endif()

endif()

project(
    Epic-Space-Shooter
    VERSION 1.0
    DESCRIPTION "OOP Group project"
    LANGUAGES ${LANGUAGES})

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CONAN_DISABLE_CHECK_COMPILER TRUE)
set(CONAN_SYSTEM_INCLUDES ON) # Prevent linting dependencies
set(CMAKE_COLOR_MAKEFILE ON)
set(CMAKE_COLOR_DIAGNOSTICS ON)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS src/*.cpp src/*.hpp)

if(ENABLE_LINT)
    message("Linting enabled")
    find_program(IWYU_PATH NAMES include-what-you-use iwyu REQUIRED)
    find_program(PYTHON_PATH NAMES python python3 REQUIRED)
    find_program(NAMES clang-tidy REQUIRED)
    find_program(NAMES clang-format REQUIRED)
    set(CMAKE_CXX_CLANG_TIDY clang-tidy)
    add_custom_target(
        iwyu ALL
        COMMAND ${PYTHON_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/tools/iwyu-tool.py -p
                ${CMAKE_BINARY_DIR}
        COMMENT "Checking include-what-you-use")
    add_custom_target(
        clang-format ALL
        COMMAND
            ${PYTHON_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/tools/run-clang-format.py
            ${SOURCE_FILES}
        COMMENT "Checking formatting")
endif()

add_compile_options(-Wall -Wextra -Wpedantic)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE src)
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})

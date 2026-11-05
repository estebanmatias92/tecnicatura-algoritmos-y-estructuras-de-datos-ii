cmake_minimum_required(VERSION 3.20)

project(drone_ibag151 VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(PROJECT_WARNINGS "")
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    list(APPEND PROJECT_WARNINGS -Wall -Wextra -Wpedantic)
endif()

option(DRONE_WARNINGS_AS_ERRORS "Treat compiler warnings as errors" OFF)
if(DRONE_WARNINGS_AS_ERRORS)
    list(APPEND PROJECT_WARNINGS -Werror)
endif()

# Core library: domain model and adapters, independent of the console entry point.
add_library(drone_core STATIC
    src/drone_ibag151.cpp
)

add_library(ibag151::drone_core ALIAS drone_core)

target_include_directories(drone_core
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

target_compile_options(drone_core PRIVATE ${PROJECT_WARNINGS})

# Console application.
add_executable(drone_ibag151
    src/main.cpp
)

target_link_libraries(drone_ibag151 PRIVATE drone_core)
target_compile_options(drone_ibag151 PRIVATE ${PROJECT_WARNINGS})

option(DRONE_BUILD_TESTS "Build the unit test suite" ON)
if(DRONE_BUILD_TESTS)
    include(CTest)
    enable_testing()
    add_subdirectory(tests)
endif()

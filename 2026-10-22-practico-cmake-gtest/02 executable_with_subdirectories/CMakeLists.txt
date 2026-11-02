cmake_minimum_required(VERSION 3.20)
project(geometries LANGUAGES CXX)

add_executable(app)
target_sources(app PRIVATE "app.cpp")
target_include_directories(app PRIVATE "${PROJECT_SOURCE_DIR}")
add_subdirectory("shape")
add_subdirectory("square")
install(TARGETS app)


#add_executable(): is to define target.app
#target_sources(): to add the source in the currrent directory, , to target.app.cppapp
#target_include_directories(): To tell CMake that the project directory tree contains headers. In this way, we can have headers from different directories added to each other with a relative path to the project directory. For example, can have .square.h#include "shape/shape.h"
#PRIVATE: for means the added files and directories are just for creating targets, not for linking to them.target_*
#1add_subdirectory(): to tell CMake to go into those subdirectories as there are more logics there in their files.CMakeLists.txt
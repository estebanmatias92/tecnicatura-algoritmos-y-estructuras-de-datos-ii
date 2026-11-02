cmake_minimum_required(VERSION 3.23)
project(geometry LANGUAGES CXX)

#Necessary for shared library on Windows
if (MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

add_library(geo SHARED)
target_include_directories(geo PRIVATE "${PROJECT_SOURCE_DIR}")
add_subdirectory("shape")
add_subdirectory("square")

add_executable(app)
target_sources(app PRIVATE "example/app.cpp")
target_link_libraries(app PRIVATE geo)


install(TARGETS geo FILE_SET HEADERS)


#if (MSVC): checking CMake is employing MS Visual C++.
#CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS: This is necessary for MSVC to create a symbol file, , besides a shared library, ..lib.dll
#add_library(): to define a library target, . means a shared library, you can also make a static library with keyword, or an object file with keyword.geoSHAREDSTATICOBJECT
#target_include_directories(): is for making source files aware of the location of private headers relative to the project directory.
#target_link_libraries(): to tell CMake that is dependent on library. So first compile then link it to executable.appgeogeoapp
#install(TARGETS): to install compiled libraries and their headers in the assigned install directory you set when running . Executables and windows dll files go into directory, libraries go into directory, and public headers go into directory at the destination. has keywords to fine-tune the destination directories, see this example:cmake --install blah blahbinlibincludeInstall(TARGETS)
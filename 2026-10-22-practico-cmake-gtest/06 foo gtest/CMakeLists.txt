cmake_minimum_required(VERSION 3.10)

project(foobar CXX)
set(CMAKE_CXX_STANDARD 17)

enable_testing()

add_subdirectory(libfoobar)
add_subdirectory(foobar)
#add_subdirectory(foobar-test) link

message("Testing enabled")
file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/foobar-test/Test.cpp ${PROJECT_SOURCE_DIR}/library/*.cpp )
#file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_subdirectory(ext/googletest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/libfolder ${gtest_SOURCE_DIR})
add_executable(runUnitTests ${TEST_SRC_FILES})
target_link_libraries(runUnitTests gtest gtest_main libfoobar)
add_test(UnitTests runUnitTests)
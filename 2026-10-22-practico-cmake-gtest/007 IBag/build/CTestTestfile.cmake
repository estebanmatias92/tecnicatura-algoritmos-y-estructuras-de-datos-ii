# CMake generated Testfile for 
# Source directory: /Users/jloemig/CMake/007 IBag
# Build directory: /Users/jloemig/CMake/007 IBag/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(UnitTests "runUnitTests")
set_tests_properties(UnitTests PROPERTIES  _BACKTRACE_TRIPLES "/Users/jloemig/CMake/007 IBag/CMakeLists.txt;21;add_test;/Users/jloemig/CMake/007 IBag/CMakeLists.txt;0;")
subdirs("ext/googletest")

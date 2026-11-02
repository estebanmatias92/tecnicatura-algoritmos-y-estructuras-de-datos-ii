# CMake generated Testfile for 
# Source directory: /Users/jloemig/CMake/six
# Build directory: /Users/jloemig/CMake/six/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(UnitTests "runUnitTests")
set_tests_properties(UnitTests PROPERTIES  _BACKTRACE_TRIPLES "/Users/jloemig/CMake/six/CMakeLists.txt;50;add_test;/Users/jloemig/CMake/six/CMakeLists.txt;0;")
subdirs("ext/googletest")

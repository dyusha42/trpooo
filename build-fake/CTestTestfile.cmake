# CMake generated Testfile for 
# Source directory: /home/q/rep/trpo/openblas-interface-tests
# Build directory: /home/q/rep/trpo/openblas-interface-tests/build-fake
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(cblas_interface_tests "/home/q/rep/trpo/openblas-interface-tests/build-fake/cblas_interface_tests")
set_tests_properties(cblas_interface_tests PROPERTIES  _BACKTRACE_TRIPLES "/home/q/rep/trpo/openblas-interface-tests/CMakeLists.txt;39;add_test;/home/q/rep/trpo/openblas-interface-tests/CMakeLists.txt;0;")
subdirs("_deps/googletest-build")

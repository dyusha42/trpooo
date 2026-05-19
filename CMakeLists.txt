cmake_minimum_required(VERSION 3.14)
project(OpenBLAS_Interface_Tests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(BLAS REQUIRED)

enable_testing()

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.12.1
)
FetchContent_MakeAvailable(googletest)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(cblas_interface_tests
    tests/test_level1_float.cpp
    tests/test_level1_double.cpp
    tests/test_main.cpp
)

target_link_libraries(cblas_interface_tests
    gtest
    gtest_main
    ${BLAS_LIBRARIES}
)

option(ENABLE_COVERAGE "Enable code coverage" OFF)
if(ENABLE_COVERAGE)
    target_compile_options(cblas_interface_tests PRIVATE --coverage)
    target_link_options(cblas_interface_tests PRIVATE --coverage)
endif()

add_test(NAME cblas_interface_tests COMMAND cblas_interface_tests)

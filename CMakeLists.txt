cmake_minimum_required(VERSION 3.10)
project(BlasBenchmark)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native")

find_package(OpenMP REQUIRED)

add_executable(benchmark main.cpp)

target_link_libraries(benchmark PRIVATE OpenMP::OpenMP_CXX)

target_link_libraries(benchmark PRIVATE openblas)
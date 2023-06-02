cmake_minimum_required(VERSION 3.8.2)

project(recursion_demo)
set(CMAKE_CXX_STANDARD 14)

# Add a compiler flag
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

find_package(glog REQUIRED)
find_package(gflags REQUIRED)

add_executable(recursion_demo RecursionDemo.cpp)
target_link_libraries(recursion_demo glog::glog)
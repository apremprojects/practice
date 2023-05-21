cmake_minimum_required(VERSION 3.8.2)

project(operator_overload)

set(CMAKE_CXX_STANDARD 17)

# Add a compiler flag
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

find_package(glog REQUIRED)
find_package(gflags REQUIRED)

add_executable(example0 example0.cpp)
target_link_libraries(example0 glog::glog)

add_executable(example1 example1.cpp)
target_link_libraries(example1 glog::glog)

add_executable(example2 example2.cpp)
target_link_libraries(example2 glog::glog)

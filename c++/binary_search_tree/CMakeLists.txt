cmake_minimum_required(VERSION 3.8.2)

project(bst)

set(CMAKE_CXX_STANDARD 17)

# Add a compiler flag
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

find_package(glog REQUIRED)
find_package(gflags REQUIRED)
find_package(GTest REQUIRED)

add_executable(bst bst.cpp)
target_link_libraries(bst glog::glog)

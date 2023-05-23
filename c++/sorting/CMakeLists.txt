cmake_minimum_required(VERSION 3.8.2)

project(sorting)

set(CMAKE_CXX_STANDARD 14)

# Add a compiler flag
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

find_package(glog REQUIRED)
find_package(gflags REQUIRED)
find_package(GTest REQUIRED)

add_executable(record_sorting record_sorting.cpp)
target_link_libraries(record_sorting glog::glog)

add_executable(point_sorting point_sorting.cpp)
target_link_libraries(point_sorting glog::glog)

add_executable(pair_sorting pair_sorting.cpp)
target_link_libraries(pair_sorting glog::glog)

add_executable(object_sorting object_sorting.cpp)
target_link_libraries(object_sorting glog::glog)

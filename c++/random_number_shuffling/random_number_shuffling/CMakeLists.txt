cmake_minimum_required(VERSION 3.8.2)

project(random_number_shuffling)
set(CMAKE_CXX_STANDARD 14)

# Add a compiler flag
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

find_package(glog REQUIRED)
find_package(gflags REQUIRED)

add_executable(random_number_shuffling random_number_shuffling.cpp)
target_link_libraries(random_number_shuffling glog::glog)
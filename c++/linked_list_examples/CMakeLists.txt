cmake_minimum_required(VERSION 3.8.2)

project(linked_list_examples)

set(CMAKE_CXX_STANDARD 17)

# Add a compiler flag
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

find_package(glog REQUIRED)
find_package(gflags REQUIRED)
find_package(GTest REQUIRED)

add_executable(stack_example stack.h stack_example.cpp)
target_link_libraries(stack_example glog::glog)

add_executable(queue_example queue.h queue_example.cpp)
target_link_libraries(queue_example glog::glog)

add_executable(doubly_linked_list doubly_linked_list.h doubly_linked_list_example.cpp)
target_link_libraries(doubly_linked_list glog::glog)

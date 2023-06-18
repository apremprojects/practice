cmake_minimum_required(VERSION 3.8.2)

project(LinkedListDemo)
set(CMAKE_CXX_STANDARD 14)

# Add a compiler flag
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")


add_executable(LinkedListDemo LinkedListDemo.cpp)
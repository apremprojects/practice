cmake_minimum_required(VERSION 3.8.2)

project(matrix)

# Turn on automatic invocation of the MOC, UIC & RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 14)

# Add a compiler flag
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

find_package(glog REQUIRED)
find_package(gflags REQUIRED)
find_package(GTest REQUIRED)

add_library(matrix INTERFACE matrix.h)

add_executable(access_elements_test access_elements_test.cpp)
target_link_libraries(access_elements_test glog::glog GTest::gtest GTest::gtest_main matrix)

add_executable(serialize_deserialize_test serialize_deserialize_test.cpp)
target_link_libraries(serialize_deserialize_test glog::glog GTest::gtest GTest::gtest_main matrix)

add_executable(add_test add_test.cpp)
target_link_libraries(add_test glog::glog GTest::gtest GTest::gtest_main matrix)

add_executable(transpose_test transpose_test.cpp)
target_link_libraries(transpose_test glog::glog GTest::gtest GTest::gtest_main matrix)

add_executable(multiply_test multiply_test.cpp)
target_link_libraries(multiply_test glog::glog GTest::gtest GTest::gtest_main matrix)
cmake_minimum_required(VERSION 3.8.2)

project(ellipsoid_fit)

# Find includes in the build directories
#set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Turn on automatic invocation of the MOC, UIC & RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 14)

# Add a compiler flag
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

find_package(gflags REQUIRED)
find_package (Eigen3 3.3 REQUIRED NO_MODULE)

add_executable(ellipsoid_fit ellipsoid_fit.cpp)
target_link_libraries(ellipsoid_fit Eigen3::Eigen)

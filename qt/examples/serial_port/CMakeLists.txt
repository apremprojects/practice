cmake_minimum_required(VERSION 3.8.2)

project(serial_port)

# Turn on automatic invocation of the MOC, UIC & RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 14)

# Add a compiler flag
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Find the Qtimages library
find_package(gflags REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS Widgets SerialPort)
find_package (Eigen3 3.3 REQUIRED NO_MODULE)

add_executable(serial_port widget.h widget.cpp main.cpp)
target_link_libraries(serial_port Qt5::SerialPort Qt5::Widgets)

cmake_minimum_required(VERSION 3.8.2)

project(signals_slots)

# Turn on automatic invocation of the MOC, UIC & RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 14)

# Add a compiler flag
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Find the Qtsignals_slotss library
find_package(gflags REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS Widgets)
find_package (Eigen3 3.3 REQUIRED NO_MODULE)

add_executable(signals_slots 
	main.cpp 
	widget.h 
	widget.cpp)
target_link_libraries(signals_slots Qt5::Widgets)

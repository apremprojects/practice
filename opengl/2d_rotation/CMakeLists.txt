cmake_minimum_required(VERSION 3.8.2)

project(2d_rotation)

# Turn on automatic invocation of the MOC, UIC & RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 14)

# Add a compiler flag
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Find the QtWidgets library
find_package(Qt5 REQUIRED COMPONENTS Widgets)
find_package (Eigen3 3.3 REQUIRED NO_MODULE)

add_subdirectory(./../helper helper)

add_executable(2d_rotation 
	main.cpp 
	widget_gl.h 
	widget_gl.cpp
	main_dlg.h
	main_dlg.cpp)
target_link_libraries(2d_rotation Qt5::Widgets)
target_link_libraries(2d_rotation helper_opengl)

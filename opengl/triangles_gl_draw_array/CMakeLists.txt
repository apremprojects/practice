cmake_minimum_required(VERSION 3.8.2)

project(triangles_gl_draw_array)

# Turn on automatic invocation of the MOC, UIC & RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 14)

# Add a compiler flag
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Find the QtWidgets library
find_package(gflags REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS Widgets)
find_package (Eigen3 3.3 REQUIRED NO_MODULE)

add_subdirectory(./../helper helper)

add_executable(triangles_gl_draw_array 
	main.cpp 
	gl_window.h 
	gl_window.cpp)
target_link_libraries(triangles_gl_draw_array Qt5::Widgets)
target_link_libraries(triangles_gl_draw_array helper_opengl)

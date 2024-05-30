cmake_minimum_required(VERSION 3.10)
project(graphics)

find_package(OpenGL REQUIRED)

include_directories(include)
link_directories(${OPENGL_LIBRARY_DIRS})

add_subdirectory(libs)
add_subdirectory(src)
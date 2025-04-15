# Project Properties
cmake_minimum_required(VERSION 3.10)
project(graphics)

# Settings
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Includes
include_directories(
  "include"
  "libs/headers"
)

# Main Binary
add_subdirectory(libs)
add_subdirectory(src)

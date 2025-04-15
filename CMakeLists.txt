# Project Properties
cmake_minimum_required(VERSION 3.10)
project(graphics)

# Settings
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(ENABLE_VULKAN "Enable Vulkan backend" ON)
option(ENABLE_DIRECTX "Enable DirectX backend" OFF)

# Includes
include_directories(
  "include"
  "libs/headers"
)

# Definitions
if (ENABLE_VULKAN)
  add_definitions(-DENGINE_VULKAN)
endif()
if (ENABLE_DIRECTX)
  add_definitions(-DENGINE_DIRECTX)
endif()

# Main Binary
add_subdirectory(libs)
add_subdirectory(src)

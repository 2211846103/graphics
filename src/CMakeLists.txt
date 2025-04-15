add_subdirectory(resources)
add_subdirectory(renderer)

add_executable(graphics main.cpp)

target_link_libraries(graphics glfw glad)
target_link_libraries(graphics renderer resources)

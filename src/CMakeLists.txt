#add_subdirectory(resources)
add_subdirectory(renderer)

add_executable(graphics main.cpp)

target_link_libraries(graphics glfw)
target_link_libraries(graphics renderer)

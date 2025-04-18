file(GLOB SRC "*.cpp" "*.mm")

add_library(renderer ${SRC})

target_link_libraries(renderer glfw d3d11)

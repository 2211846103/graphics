add_subdirectory(resources)

add_executable(graphics main.cpp)

target_link_directories(graphics PRIVATE resources)

file(GLOB SOURCES "*.cpp" "*.c")

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} glfw ${OPENGL_LIBRARIES})
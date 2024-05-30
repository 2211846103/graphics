#include "window.hpp"

GRAPHICS::WINDOW::WINDOW(int w, int h, char* name) : _width{w}, _height{h}, _windowName{name} {
    glfwInit();
}

GRAPHICS::WINDOW::~WINDOW() {
    glfwDestroyWindow(window);

    glfwTerminate();
}

void GRAPHICS::WINDOW::initWindow() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __MACH__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    window = glfwCreateWindow(_width, _height, _windowName, nullptr, nullptr);
}
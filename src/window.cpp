#include "window.hpp"

Graphics::Window::Window(int w, int h, char* name) : _width{w}, _height{h}, _windowName{name} {
    initWindow();
}

Graphics::Window::~Window() {
    glfwDestroyWindow(_window);

    glfwTerminate();
}

bool Graphics::Window::shouldClose() {
    return glfwWindowShouldClose(_window);
}

void Graphics::Window::update() {
    glfwPollEvents();
    glfwSwapBuffers(_window);
}

void Graphics::Window::initWindow() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __MACH__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    _window = glfwCreateWindow(_width, _height, _windowName, nullptr, nullptr);
}
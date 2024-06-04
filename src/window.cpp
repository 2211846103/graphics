#include "window.hpp"

using namespace Graphics;

Window::Window(int w, int h, char* name) : width{w}, height{h}, windowName{name} {
    initWindow();
}

Window::~Window() {
    glfwDestroyWindow(window);

    glfwTerminate();
}

bool Window::shouldClose() {
    return glfwWindowShouldClose(window);
}

// Window methods that need to be called in the render loop.
void Window::update() {
    glfwPollEvents();
    glfwSwapBuffers(window);
}

void Window::clear(float red, float green, float blue) {
    glClearColor(red, green, blue, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::initWindow() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __MACH__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    window = glfwCreateWindow(width, height, windowName, nullptr, nullptr);
    glfwMakeContextCurrent(window);
    gladLoadGL();
}
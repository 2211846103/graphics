#include "window.hpp"

using namespace Graphics;

Window::Window(int w, int h, const char* name) : width{w}, height{h}, windowName{name} {
    initWindow();
}

Window::~Window() {
    glfwDestroyWindow(_window);
    glfwTerminate();
}

bool Window::shouldClose() {
    return glfwWindowShouldClose(_window);
}

// Window methods that need to be called in the render loop.
float Window::update() {
    glfwPollEvents();
    glfwSwapBuffers(_window);

    float currentFrame = glfwGetTime();
    float deltaTime = currentFrame - _lastFrame;
    _lastFrame = currentFrame; 

    return deltaTime;
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

    _window = glfwCreateWindow(width, height, windowName, nullptr, nullptr);
    glfwMakeContextCurrent(_window);
    gladLoadGL();
}

void Window::setSizeCallback(void (*callback)(GLFWwindow* window, int width, int height)) {
    glfwSetFramebufferSizeCallback(this->_window, *callback);
}
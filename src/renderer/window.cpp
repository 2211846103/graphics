#include <renderer/window.hpp>

using namespace engine::rendering;

OpenGLWindow::OpenGLWindow(int w, int h, const char* name) : _width(w), _height(h), _windowName(name) {}

OpenGLWindow::~OpenGLWindow() {
    glfwDestroyWindow(_window);
    glfwTerminate();
}

void OpenGLWindow::initWindow() {
    _window = glfwCreateWindow(_width, _height, _windowName, nullptr, nullptr);
    glfwMakeContextCurrent(_window);

    glfwSetWindowUserPointer(this->_window, this);
}

float OpenGLWindow::update() {
    glfwPollEvents();
    glfwSwapBuffers(_window);

    float currentFrame = glfwGetTime();
    float deltaTime = currentFrame - _lastFrame;
    _lastFrame = currentFrame;

    return deltaTime;
}

bool OpenGLWindow::shouldClose() {
    return glfwWindowShouldClose(_window);
}

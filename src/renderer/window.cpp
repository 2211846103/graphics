#include <renderer/window.hpp>
#include <iostream>


using namespace engine::rendering;

#ifdef ENGINE_COMPILE_OPENGL
OpenGLWindow::OpenGLWindow(int width, int height, const char* name) : _width(width), _height(height), _windowName(name) {}

OpenGLWindow::~OpenGLWindow() {
    glfwDestroyWindow(_window);
    glfwTerminate();
}

void OpenGLWindow::initWindow() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return;
    }

    _window = glfwCreateWindow(_width, _height, _windowName, nullptr, nullptr);

    glfwMakeContextCurrent(_window);

    glfwSetWindowUserPointer(this->_window, this);
}

float OpenGLWindow::update() {
    glfwSwapBuffers(_window);
    glfwPollEvents();

    float currentFrame = glfwGetTime();
    float deltaTime = currentFrame - _lastFrame;
    _lastFrame = currentFrame;

    return deltaTime;
}

bool OpenGLWindow::shouldClose() {
    return glfwWindowShouldClose(_window);
}
#endif

#ifdef ENGINE_COMPILE_VULKAN
VulkanWindow::VulkanWindow(int width, int height, const char* name) : _width(width), _height(height), _windowName(name) {}

VulkanWindow::~VulkanWindow(){
    glfwDestroyWindow(_window);
    glfwTerminate();
}

void VulkanWindow::initWindow(){
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    _window = glfwCreateWindow(_width, _height, _windowName, nullptr, nullptr);
}

float VulkanWindow::update(){
    glfwPollEvents();
}

bool VulkanWindow::shouldClose(){
    return glfwWindowShouldClose(_window);
}
#endif
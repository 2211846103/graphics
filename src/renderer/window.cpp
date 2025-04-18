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

#ifdef ENGINE_COMPILE_DIRECTX

device = nullptr;
context = nullptr;
swampChain = nullptr;

DirectXWindow::DirectXWindow(int width, int height, const char* name) : _width(width), _height(height), _windowName(name) {}

DirectXWindow::~DirectXWindow(){
    glfwDestroyWindow(_window);
    glfwTerminate();
}

void DirectXWindow::initWindow(){
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    _window = glfwCreateWindow(_width, _height, _windowName, nullptr, nullptr);
    HWND hwnd = glfwGetWin32Window(_window);
    
    DXGI_SWAP_CHAIN_DESC scd = {};
    scd.BufferCount = 1;
    scd.BufferDesc.Width = 800;
    scd.BufferDesc.Height = 600;
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scd.OutputWindow = hwnd;
    scd.SampleDesc.Count = 1;
    scd.Windowed = TRUE;
    scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    HRESULT hr = D3D11CreateDeviceAndSwapChain(
        nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0,
        nullptr, 0, D3D11_SDK_VERSION,
        &scd, &swapChain, &device, nullptr, &context
    );
}

float DirextXWindow::update(){
    glfwPollEvents();

    float clearColor[] = {0.1f, 0.2f, 0.3f, 1.0f};
    context->ClearRenderTargetView(renderTargetView, clearColor);
    swapChain->Present(1,0);
}

bool DirextXWindow::shouldClose(){
    return glfwWindowShouldClose(_window);
}
#endif
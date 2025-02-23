#include <graphics_api.hpp>
#include <scene.hpp>
#include <component.hpp>

using namespace Graphics;

static int viewport_width, viewport_height;

static void opengl_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);

    Window* instance = static_cast<Window*>(glfwGetWindowUserPointer(window));
    instance->width = width;
    instance->height = height;

    viewport_width = width;
    viewport_height = height;
}

OpenGLGraphicsAPI::OpenGLGraphicsAPI(Window& window) {
    glfwInit();
    
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __MACH__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    window.initWindow();

    gladLoadGL();
    glViewport(0, 0, window.width, window.height);
    viewport_width = window.width;
    viewport_height = window.height;
    window.setSizeCallback(opengl_size_callback);
}

Buffer* OpenGLGraphicsAPI::createBuffer(BufferType type, void* data, size_t size, BufferUsage usage) {
    return new OpenGLBuffer(type, data, size, usage);
}

Shader* OpenGLGraphicsAPI::createShader(const char* vPath, const char* fPath) {
    return new OpenGLShader(vPath, fPath);
}

ComputeShader* OpenGLGraphicsAPI::createComputeShader(const char* path) {
    return new OpenGLComputeShader(path);
}

VertexArray* OpenGLGraphicsAPI::createVertexArray() {
    return new OpenGLVertexArray();
}

Texture2D* OpenGLGraphicsAPI::createTexture2D(const char* path) {
    return new Texture2D(new OpenGLTexture(), path);
}

Texture2D* OpenGLGraphicsAPI::createTexture2D(Vec4 color) {
    return new Texture2D(new OpenGLTexture(), color);
}

Texture3D* OpenGLGraphicsAPI::createTexture3D(const char* path[], size_t size) {
    return new Texture3D(new OpenGLTexture(), path, size);
}

TextureCube* OpenGLGraphicsAPI::createTextureCube(const char* path[], size_t size) {
    return new TextureCube(new OpenGLTexture(), path, size);
}

void OpenGLGraphicsAPI::enableZBuffer() {
    glEnable(GL_DEPTH_TEST);
    this->_channelBuffers |= GL_DEPTH_BUFFER_BIT;
}

void OpenGLGraphicsAPI::setClearColor(Vec3 color) {
    glClearColor(color.x(), color.y(), color.z(), 1.0);
}

void OpenGLGraphicsAPI::clear() {
    glClear(this->_channelBuffers);
}

void GraphicsAPI::getDimensions(int* width, int* height) {
    *width = viewport_width;
    *height = viewport_height;
}
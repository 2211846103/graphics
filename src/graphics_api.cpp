#include <graphics_api.hpp>

using namespace Graphics;

static void opengl_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);

    Window* instance = static_cast<Window*>(glfwGetWindowUserPointer(window));
    instance->width = width;
    instance->height = height;
}

OpenGLGraphicsAPI::OpenGLGraphicsAPI(Window& window) {
    gladLoadGL();
    glViewport(0, 0, window.width, window.height);
    window.setSizeCallback(opengl_size_callback);
}

Buffer* OpenGLGraphicsAPI::createBuffer(BufferType type, void* data, size_t size, BufferUsage usage) {
    return new OpenGLBuffer(type, data, size, usage);
}

Shader* OpenGLGraphicsAPI::createShader(const char* vPath, const char* fPath) {
    return new OpenGLShader(vPath, fPath);
}

VertexArray* OpenGLGraphicsAPI::createVertexArray(Vertex* vertices, size_t size) {
    return new OpenGLVertexArray(vertices, size);
}

Texture2D* OpenGLGraphicsAPI::createTexture2D(const char* path) {
    return new Texture2D(new OpenGLTexture(), path);
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
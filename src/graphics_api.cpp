#include <graphics_api.hpp>

using namespace Graphics;

OpenGLGraphicsAPI::OpenGLGraphicsAPI(Window& window) {
    glViewport(0, 0, window.width, window.height);
}

Buffer* OpenGLGraphicsAPI::createBuffer(BufferType type, void* data, BufferUsage usage) {
    return new OpenGLBuffer(type, data, usage);
}

Shader* OpenGLGraphicsAPI::createShader(const char* vPath, const char* fPath) {
    return new OpenGLShader(vPath, fPath);
}
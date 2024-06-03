#include <graphics_api_backup.hpp>

using namespace Graphics;

void OpenGLGraphics::init(Window &window) {
    glViewport(0, 0, window.width, window.height);
}

Buffer* OpenGLGraphics::createBuffer(BufferType type, void* data, BufferUsage usage) {
    return new OpenGLBuffer(type, data, usage);
}

VertexArray* OpenGLGraphics::createVertexArray(float* vertices, int vertexCount) {
    return new OpenGLVertexArray(vertices, vertexCount);
}

void OpenGLGraphics::draw(VertexArray* vertexArray, Shader& shader, Texture& texture) {}
std::unique_ptr<Shader> OpenGLGraphics::createShader(char* vertexSource, char* fragmentSource) {}
std::unique_ptr<Texture> OpenGLGraphics::createTexture(char* path) {}
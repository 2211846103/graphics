#include <graphics_api.hpp>

using namespace Graphics;

void OpenGLGraphics::init(Window &window) {
    glViewport(0, 0, window.width, window.height);
}

Buffer* OpenGLGraphics::createBuffer(BufferType type, void* data, BufferUsage usage) {
    return new OpenGLBuffer(type, data, usage);
}

std::unique_ptr<VertexArray> OpenGLGraphics::createVertexArray(float* vertices, int vertexCount) {
    std::unique_ptr<OpenGLVertexArray> vertexArray(new OpenGLVertexArray);
    vertexArray->vertexCount = vertexCount;
    glGenVertexArrays(1, &vertexArray->id);
    vertexArray->bind();

    Buffer* vertexBuffer = createBuffer(VertexBuffer, vertices, StaticDraw);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
    glEnableVertexAttribArray(0);

    vertexArray->vertexBuffer = vertexBuffer;
    return std::move(vertexArray);
}

void OpenGLGraphics::draw(VertexArray* vertexArray, Shader& shader, Texture& texture) {}
std::unique_ptr<Shader> OpenGLGraphics::createShader(char* vertexSource, char* fragmentSource) {}
std::unique_ptr<Texture> OpenGLGraphics::createTexture(char* path) {}
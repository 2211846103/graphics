#include <graphics_api.hpp>

using namespace Graphics;

void OpenGLGraphics::init(Window &window) {
    glViewport(0, 0, window.width, window.height);
}

std::unique_ptr<Buffer> OpenGLGraphics::createBuffer(BufferType type, void* data, BufferUsage usage) {
    std::unique_ptr<OpenGLBuffer> buffer = std::make_unique<OpenGLBuffer>();

    switch(usage) {
        case StaticDraw:
            buffer->usage = GL_STATIC_DRAW; break;
        case DynamicDraw:
            buffer->usage = GL_DYNAMIC_DRAW; break;
        case StreamDraw:
            buffer->usage = GL_STREAM_DRAW; break;
        case StaticCopy:
            buffer->usage = GL_STATIC_COPY; break;
        case DynamicCopy:
            buffer->usage = GL_DYNAMIC_COPY; break;
        case StreamCopy:
            buffer->usage = GL_STREAM_COPY; break;
        case StaticRead:
            buffer->usage = GL_STATIC_READ; break;
        case DynamicRead:
            buffer->usage = GL_DYNAMIC_READ; break;
        case StreamRead:
            buffer->usage = GL_STREAM_READ; break;
        default:
            buffer->usage = 0;
    }
    
    glGenBuffers(1, &buffer->id);
    buffer->bind(type);
    buffer->setData(data);
    buffer->unbind();

    return std::move(buffer);
}

std::unique_ptr<VertexArray> OpenGLGraphics::createVertexArray(float* vertices, int vertexCount) {
    std::unique_ptr<OpenGLVertexArray> vertexArray = std::make_unique<OpenGLVertexArray>();
    vertexArray->vertexCount = vertexCount;
    glGenVertexArrays(1, &vertexArray->id);
    vertexArray->bind();

    std::unique_ptr<Buffer> vertexBuffer = createBuffer(VertexBuffer, vertices, StaticDraw);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
    glEnableVertexAttribArray(0);

    vertexArray->vertexBuffer = std::move(vertexBuffer);
    return std::move(vertexArray);
}

void OpenGLGraphics::draw(VertexArray* vertexArray, Shader& shader, Texture& texture) {}
std::unique_ptr<Shader> OpenGLGraphics::createShader(char* vertexSource, char* fragmentSource) {}
std::unique_ptr<Texture> OpenGLGraphics::createTexture(char* path) {}
#include <graphics_api.hpp>

using namespace Graphics;

Vertex::Vertex(float x, float y, float z) {
    this->position[0] = x;
    this->position[1] = y;
    this->position[2] = z;
}

void OpenGLGraphics::init(Window &window) {
    glViewport(0, 0, window.width, window.height);
}

Buffer OpenGLGraphics::createBuffer(BufferType type, void* data, BufferUsage usage) {
    OpenGLBuffer buffer;

    switch(usage) {
        case StaticDraw:
            buffer.usage = GL_STATIC_DRAW; break;
        case DynamicDraw:
            buffer.usage = GL_DYNAMIC_DRAW; break;
        case StreamDraw:
            buffer.usage = GL_STREAM_DRAW; break;
        case StaticCopy:
            buffer.usage = GL_STATIC_COPY; break;
        case DynamicCopy:
            buffer.usage = GL_DYNAMIC_COPY; break;
        case StreamCopy:
            buffer.usage = GL_STREAM_COPY; break;
        case StaticRead:
            buffer.usage = GL_STATIC_READ; break;
        case DynamicRead:
            buffer.usage = GL_DYNAMIC_READ; break;
        case StreamRead:
            buffer.usage = GL_STREAM_READ; break;
        default:
            buffer.usage = 0;
    }
    
    glGenBuffers(1, &buffer.id);
    buffer.bind(type);

    return buffer;
}

VertexArray OpenGLGraphics::createVertexArray(Vertex* vertices) {
    OpenGLVertexArray vertexArray;
    vertexArray.vertexCount = sizeof(vertices) / sizeof(Vertex);
    
    Buffer vertexBuffer = createBuffer(VertexBuffer, vertices, StaticDraw);
    vertexArray.setVertexBuffer(vertexBuffer);

    glGenVertexArrays(1, &vertexArray.id);
    vertexArray.bind();

    vertexArray.vertexBuffer.bind(VertexBuffer);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices->position), (void*)0);

    vertexArray.unbind();

    return vertexArray;
}

void OpenGLGraphics::draw(VertexArray& vertexArray, Shader& shader, Texture& texture) {

}
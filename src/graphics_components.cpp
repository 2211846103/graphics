#include <graphics_components.hpp>

using namespace Graphics;

OpenGLBuffer::OpenGLBuffer(BufferType type, void* data, BufferUsage usage) {
    switch(usage) {
        case StaticDraw:
            this->usage = GL_STATIC_DRAW; break;
        case DynamicDraw:
            this->usage = GL_DYNAMIC_DRAW; break;
        case StreamDraw:
            this->usage = GL_STREAM_DRAW; break;
        case StaticCopy:
            this->usage = GL_STATIC_COPY; break;
        case DynamicCopy:
            this->usage = GL_DYNAMIC_COPY; break;
        case StreamCopy:
            this->usage = GL_STREAM_COPY; break;
        case StaticRead:
            this->usage = GL_STATIC_READ; break;
        case DynamicRead:
            this->usage = GL_DYNAMIC_READ; break;
        case StreamRead:
            this->usage = GL_STREAM_READ; break;
        default:
            this->usage = 0;
    }
    
    glGenBuffers(1, &this->id);
    bind(type);
    setData(data);
}

void OpenGLBuffer::bind() {
    glBindBuffer(this->type, id);
}

OpenGLBuffer::~OpenGLBuffer() {
    OpenGLBuffer::unbind();
}

void OpenGLBuffer::bind(BufferType type) {
    switch(type) {
        case VertexBuffer:
            this->type = GL_ARRAY_BUFFER; break;
        case IndexBuffer:
            this->type = GL_ELEMENT_ARRAY_BUFFER; break;
        case UniformBuffer:
            this->type = GL_UNIFORM_BUFFER; break;
        case TextureBuffer:
            this->type = GL_TEXTURE_BUFFER; break;
        case ShaderStorageBuffer:
            this->type = GL_SHADER_STORAGE_BUFFER; break;
        default:
            this->type = 0;
    }

    glBindBuffer(this->type, this->id);
}

void OpenGLBuffer::unbind() {
    glBindBuffer(this->type, 0);
}

void OpenGLBuffer::setData(void* data) {
    this->data = data;
    glBufferData(this->type, sizeof(data), data, this->usage);
}

OpenGLVertexArray::OpenGLVertexArray(float* vertices, int vertexCount) {
    this->vertexCount = vertexCount;
    glGenVertexArrays(1, &this->id);
    bind();

    Buffer* vertexBuffer = new OpenGLBuffer(VertexBuffer, vertices, StaticDraw);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
    glEnableVertexAttribArray(0);

    this->vertexBuffer = vertexBuffer;
}

void OpenGLVertexArray::bind() {
    glBindVertexArray(this->id);
}

void OpenGLVertexArray::unbind() {
    glBindVertexArray(0);
}

void OpenGLVertexArray::draw() {
    bind();
    glDrawArrays(GL_TRIANGLES, 0, this->vertexCount);
}
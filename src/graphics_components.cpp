#include <graphics_components.hpp>

using namespace Graphics;

OpenGLBuffer::OpenGLBuffer(BufferType type, void* data, size_t size, BufferUsage usage) {
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

    switch(type) {
        case VertexBuffer:
            this->type = GL_ARRAY_BUFFER; break;
        case IndexBuffer:
            this->type = GL_ELEMENT_ARRAY_BUFFER; break;
        case UniformBuffer:
            this->type = GL_UNIFORM_BUFFER; break;
        case ShaderStorageBuffer:
            this->type = GL_SHADER_STORAGE_BUFFER; break;
        default:
            this->type = 0;
    }
    this->data = data;

    glGenBuffers(1, &this->id);
    glBindBuffer(this->type, this->id);
    glBufferData(this->type, size, data, this->usage);
}

OpenGLBuffer::~OpenGLBuffer() {
    unbind();
}

void OpenGLBuffer::bind() {
    glBindBuffer(this->type, id);
}

void OpenGLBuffer::bind(BufferType type) {
    switch(type) {
        case VertexBuffer:
            this->type = GL_ARRAY_BUFFER; break;
        case IndexBuffer:
            this->type = GL_ELEMENT_ARRAY_BUFFER; break;
        case UniformBuffer:
            this->type = GL_UNIFORM_BUFFER; break;
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

void OpenGLBuffer::setData(void* data, size_t size) {
    this->data = data;
    glBufferData(this->type, size, data, this->usage);
}

OpenGLVertexArray::OpenGLVertexArray(float vertices[], size_t size) {
    this->vertexCount = size / sizeof(float);

    glGenVertexArrays(1, &this->id);
    bind();

    Buffer* vertexBuffer = new OpenGLBuffer(VertexBuffer, vertices, size, StaticDraw);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
    glEnableVertexAttribArray(0);

    this->vertexBuffer = vertexBuffer;
}

OpenGLVertexArray::~OpenGLVertexArray() {
    unbind();
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

OpenGLTexture2D::OpenGLTexture2D(const char* path, TextureFilter filter) {
    unsigned char* imageData = stbi_load(path, &this->width, &this->height, nullptr, 4);

    

    glGenTextures(1, &this->_id);
    bind();
    setData(imageData);
    setFilter(filter);
    unbind();

    stbi_image_free(imageData);
}

OpenGLTexture2D::~OpenGLTexture2D() {
    unbind();
    glDeleteTextures(1, &this->_id);
}

void OpenGLTexture2D::bind() {
    glBindTexture(GL_TEXTURE_2D, this->_id);
}

void OpenGLTexture2D::setData(unsigned char* data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
}

void OpenGLTexture2D::setFilter(TextureFilter filter) {
    switch (filter) {
        case Linear:
            this->_filter = GL_LINEAR; break;
        case Nearest:
            this->_filter = GL_NEAREST; break;
        default:
            this->_filter = 0;
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->_filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->_filter);
}

void OpenGLTexture2D::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}
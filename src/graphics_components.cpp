#include <graphics_components.hpp>

using namespace Graphics;

std::vector<float> Vertex::toFloat() {
    return std::vector<float> ({
        position.x(), position.y(), position.z(),
        normal.x(), normal.y(), normal.z(),
        uv.x(), uv.y()
    });
}

std::vector<float> Vertex::flatten(Vertex* vertices, int count) {
    std::vector<float> data;
    data.reserve(count * vertices[0].toFloat().size());

    for (int i = 0; i < count; i++) {
        std::vector<float> vertexData = vertices[i].toFloat();
        data.insert(data.end(), vertexData.begin(), vertexData.end());
    }

    return data;
}

OpenGLBuffer::OpenGLBuffer(BufferType type, void* data, size_t size, BufferUsage usage) {
    // Buffer Usage Mapping
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

    // Create a Buffer to Store Data
    glGenBuffers(1, &this->id);
    OpenGLBuffer::bind(type);
    OpenGLBuffer::setData(data, size);
}

OpenGLBuffer::OpenGLBuffer(BufferType type) {
    glGenBuffers(1, &this->id);
    OpenGLBuffer::bind(type);
}

OpenGLBuffer::~OpenGLBuffer() {
    // Unbind and Delete Buffer
    unbind();
    glDeleteBuffers(1, &this->id);
}

void OpenGLBuffer::bind() {
    glBindBuffer(this->type, id);
}

void OpenGLBuffer::bind(BufferType type) {
    // Buffer Type Mapping
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

    // Bind Buffer to Generated Type
    glBindBuffer(this->type, this->id);
}

void OpenGLBuffer::unbind() {
    glBindBuffer(this->type, 0);
}

void OpenGLBuffer::setData(void* data, size_t size) {
    // Assign Data to the Buffer
    glBufferData(this->type, size, data, this->usage);
    this->_is_set = true;
}

bool OpenGLBuffer::isSet() {
    return this->_is_set;
}

void OpenGLBuffer::setBindingPoint(int point) {
    glBindBufferBase(this->type, point, this->id);
}

void OpenGLBuffer::getData(void* ptr, size_t size) {
    this->bind();
    glGetBufferSubData(this->type, 0, size, ptr);
}

OpenGLVertexArray::OpenGLVertexArray() {
    glGenVertexArrays(1, &this->id);
}

OpenGLVertexArray::~OpenGLVertexArray() {
    // Unbind and Delete Vertex Array
    unbind();
    glDeleteBuffers(1, &this->id);
    delete this->vertexBuffer;
    delete this->indexBuffer;
}

void OpenGLVertexArray::bind() {
    glBindVertexArray(this->id);
}

void OpenGLVertexArray::unbind() {
    glBindVertexArray(0);
}

void OpenGLVertexArray::draw() {
    // Bind Array By Triangles
    bind();
    if (this->indexBuffer->isSet()) glDrawElements(GL_TRIANGLES, this->indexCount, GL_UNSIGNED_INT, 0);
    else glDrawArrays(GL_TRIANGLES, 0, this->vertexCount);
}

void OpenGLVertexArray::bindVertices(Vertex* vertices, size_t size) {
    bind();
    this->vertexCount = size / (sizeof(Vertex));
    this->vertexBuffer = new OpenGLBuffer(VertexBuffer, Vertex::flatten(vertices, this->vertexCount).data(), size, StaticDraw);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 6));
    glEnableVertexAttribArray(2);
}

void OpenGLVertexArray::bindIndices(int* indices, size_t size) {
    bind();
    this->indexCount = size / sizeof(int);
    this->indexBuffer = new OpenGLBuffer(IndexBuffer, indices, size, StaticDraw);
}
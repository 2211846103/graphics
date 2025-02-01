#include <graphics_components.hpp>

using namespace Graphics;

std::vector<float> Vertex::toFloat() {
    return std::vector<float> ({
        position.x(), position.y(), position.z(),
        uv.x(), uv.y()
    });
}

std::vector<float> Vertex::flatten(Vertex* vertices, int count) {
    std::vector<float> data;
    data.reserve(count * vertices[0].toFloat().size()); // Each vertex has 8 floats (position + color)

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
}

OpenGLVertexArray::OpenGLVertexArray(Vertex* vertices, size_t size) {
    // Create Vertex Array and Calculate Number
    // of Vertices
    this->vertexCount = size / (sizeof(Vertex));
    glGenVertexArrays(1, &this->id);
    bind();

    // Create a new Vertex Buffer
    Buffer* vertexBuffer = new OpenGLBuffer(VertexBuffer, Vertex::flatten(vertices, this->vertexCount).data(), size, StaticDraw);

    // Specify Vertex Array Buffer Pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);

    this->vertexBuffer = vertexBuffer;
}

OpenGLVertexArray::~OpenGLVertexArray() {
    // Unbind and Delete Vertex Array
    unbind();
    glDeleteBuffers(1, &this->id);
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
    glDrawArrays(GL_TRIANGLES, 0, this->vertexCount);
}
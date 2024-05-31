#include <graphics_components.hpp>

using namespace Graphics;

void OpenGLBuffer::bind(BufferType type) {
    switch(type) {
        case VertexBuffer:
            _type = GL_ARRAY_BUFFER; break;
        case IndexBuffer:
            _type = GL_ELEMENT_ARRAY_BUFFER; break;
        case UniformBuffer:
            _type = GL_UNIFORM_BUFFER; break;
        case TextureBuffer:
            _type = GL_TEXTURE_BUFFER; break;
        case ShaderStorageBuffer:
            _type = GL_SHADER_STORAGE_BUFFER; break;
        default:
            _type = 0;
    }

    glBindBuffer(this->_type, id);
}

void OpenGLBuffer::unbind() {
    glBindBuffer(this->_type, 0);
}

void OpenGLBuffer::setData(void* data) {
    glBufferData(this->_type, sizeof(this->_data), this->_data, this->usage);
}
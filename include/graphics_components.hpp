#pragma once

#include <glad/glad.h>

namespace Graphics {
    enum BufferType {
        VertexBuffer, IndexBuffer, UniformBuffer,
        TextureBuffer, ShaderStorageBuffer
    };

    enum BufferUsage {
        StaticDraw, DynamicDraw, StreamDraw,
        StaticCopy, DynamicCopy, StreamCopy,
        StaticRead, DynamicRead, StreamRead
    };

    class Buffer {
        public:
            void* data;
            
            virtual ~Buffer() = default;

            virtual void bind() = 0;
            virtual void bind(BufferType type) = 0;
            virtual void setData(void* data) = 0;
            virtual void unbind() = 0;
    };

    class OpenGLBuffer : public Buffer {
        public:
            unsigned int id;
            GLenum type;
            GLenum usage;

            OpenGLBuffer(BufferType type, void* data, BufferUsage usage);
            ~OpenGLBuffer();

            void bind() override;
            void bind(BufferType type) override;
            void setData(void* data) override;
            void unbind() override;
    };

    class VertexArray {
        public:
            int vertexCount;
            int indexCount;

            Buffer* vertexBuffer;
            Buffer* indexBuffrt;

            virtual ~VertexArray() = default;

            virtual void bind() = 0;
            virtual void unbind() = 0;
            virtual void draw() = 0;
    };

    class OpenGLVertexArray : public VertexArray {
        public:
            unsigned int id;

            OpenGLVertexArray(float* vertices, int vertexCount);
            ~OpenGLVertexArray();

            void bind() override;
            void unbind() override;
            void draw() override;
    };
}
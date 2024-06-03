#pragma once

#include <glad/glad.h>
#include <memory>

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
        protected:
            void* _data;

        public:
            virtual ~Buffer() = default;

            virtual void bind() = 0;
            virtual void bind(BufferType type) = 0;
            virtual void unbind() = 0;
            virtual void setData(void* data) = 0;
    };

    class OpenGLBuffer : public Buffer {
        private:
            GLenum _type;

        public:
            GLuint id;
            GLenum usage;

            OpenGLBuffer(BufferType type, void* data, BufferUsage usage);

            void bind() override;
            void bind(BufferType type) override;
            void unbind() override;
            void setData(void* data) override;
    };

    class VertexArray {
        public:
            int vertexCount;
            int indexCount;
            Buffer* vertexBuffer;
            Buffer* indexBuffer;

            virtual ~VertexArray() = default;

            virtual void bind() = 0;
            virtual void unbind() = 0;
            virtual void draw() = 0;
    };

    class OpenGLVertexArray : public VertexArray {
        public:
            GLuint id;

            OpenGLVertexArray(float* vertices, int vertexCount);

            void bind() override;
            void unbind() override;
            void draw() override;
    };
}
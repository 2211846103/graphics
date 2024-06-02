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
        protected:
            void* _data;

        public:
            virtual void bind(BufferType type) {};
            virtual void unbind() {};
            virtual void setData(void* data) {};
    };

    class OpenGLBuffer : public Buffer {
        private:
            GLenum _type;

        public:
            GLuint id;
            GLenum usage;

            void bind(BufferType type);
            void unbind();
            void setData(void* data);
    };

    class VertexArray {
        public:
            int vertexCount;
            int indexCount;
            Buffer vertexBuffer;
            Buffer indexBuffer;

            virtual void setVertexBuffer(Buffer vertexBuffer) {};
            virtual void setIndexBuffer(Buffer indexBuffer) {};
            virtual void bind() {};
            virtual void unbind() {};
            virtual void draw() {};
    };

    class OpenGLVertexArray : public VertexArray {
        public:
            GLuint id;

            void setVertexBuffer(Buffer vertexBuffer);
            void setIndexBuffer(Buffer indexBuffer);
            void bind();
            void unbind();
            void draw();
    };
}
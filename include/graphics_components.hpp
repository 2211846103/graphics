#pragma once

#include <stb_image.h>
#include <glad/glad.h>
#include <iostream>

namespace Graphics {
    enum BufferType {
        VertexBuffer, IndexBuffer, UniformBuffer, ShaderStorageBuffer
    };

    enum BufferUsage {
        StaticDraw, DynamicDraw, StreamDraw,
        StaticCopy, DynamicCopy, StreamCopy,
        StaticRead, DynamicRead, StreamRead
    };

    enum TextureFilter {
        Linear, Nearest
    };

    class Buffer {
        public:
            void* data;
            
            virtual ~Buffer() = default;

            virtual void bind() = 0;
            virtual void bind(BufferType type) = 0;
            virtual void setData(void* data, size_t size) = 0;
            virtual void unbind() = 0;
    };

    class OpenGLBuffer : public Buffer {
        public:
            unsigned int id;
            GLenum type;
            GLenum usage;

            OpenGLBuffer(BufferType type, void* data, size_t size, BufferUsage usage);
            ~OpenGLBuffer();

            void bind() override;
            void bind(BufferType type) override;
            void setData(void* data, size_t size) override;
            void unbind() override;
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
            unsigned int id;

            OpenGLVertexArray(float* vertices, size_t size);
            ~OpenGLVertexArray();

            void bind() override;
            void unbind() override;
            void draw() override;
    };

    class Texture2D {
        public:
            int width;
            int height;

            virtual ~Texture2D() = default;

            virtual void bind() = 0;
            virtual void setData(unsigned char* data) = 0;
            virtual void setFilter(TextureFilter filter) = 0;
            virtual void unbind() = 0;
    };

    class OpenGLTexture2D : public Texture2D {
        private:
            unsigned int _id;
            GLenum _filter;

        public:
            OpenGLTexture2D(const char* path, TextureFilter filter);
            ~OpenGLTexture2D();

            void bind() override;
            void setData(unsigned char* data) override;
            void setFilter(TextureFilter filter) override;
            void unbind() override;
    };
}
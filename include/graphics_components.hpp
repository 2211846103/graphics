#pragma once

#include <glad/glad.h>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <math.hpp>

namespace Graphics {
    enum BufferType {
        VertexBuffer, IndexBuffer, UniformBuffer, ShaderStorageBuffer
    };

    enum BufferUsage {
        StaticDraw, DynamicDraw, StreamDraw,
        StaticCopy, DynamicCopy, StreamCopy,
        StaticRead, DynamicRead, StreamRead
    };

    class Vertex {
        public:
            Math::Vec3 position;
            Math::Vec2 uv;

            std::vector<float> toFloat();
            static std::vector<float> flatten(Vertex* vertices, int count);
    };

    class Buffer {
        protected:
            bool _is_set = false;

        public:
            virtual ~Buffer() = default;

            virtual void bind() = 0;
            virtual void bind(BufferType type) = 0;
            virtual void setData(void* data, size_t size) = 0;
            virtual bool isSet() = 0;
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
            bool isSet() override;
            void unbind() override;
    };

    class VertexArray {
        protected:
            int* _indices;

        public:
            int vertexCount;
            int indexCount;

            Buffer* vertexBuffer; // Should be Private Right?
            Buffer* indexBuffer;  // Should be Private Right?

            virtual ~VertexArray() = default;

            virtual void bind() = 0;
            virtual void unbind() = 0;
            virtual void draw() = 0;
            virtual void bindIndices(int* indices, size_t size) = 0;
    };

    class OpenGLVertexArray : public VertexArray {
        public:
            unsigned int id;

            OpenGLVertexArray(Vertex* vertices, size_t size);
            ~OpenGLVertexArray();

            void bind() override;
            void unbind() override;
            void draw() override;
            void bindIndices(int* indices, size_t size) override;
    };
}
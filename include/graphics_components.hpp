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
            virtual void bind(BufferType type);
            virtual void unbind();
            virtual void setData(void* data);
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
}
#pragma once

#include <glad/glad.h>
#include <graphics_components.hpp>

namespace Graphics {
    // Boilerplate (Don't mind it)
    struct Texture {};
    struct Shader {};
    struct VertexArray {};

    class GraphicsApi {
        public:
            virtual void init();
            virtual Texture createTexture(char* path);
            virtual Shader createShader(char* vertexSource, char* fragmentSource);
            virtual Buffer createBuffer(BufferType type, void* data, BufferUsage usage);
            virtual VertexArray createVertexArray();
            virtual void Draw(VertexArray& vertexArray, Shader& shader, Texture& texture);
    };

    class OpenGLGraphics: public GraphicsApi {
        public:
            void init(int x, int y, int width, int height);
            Buffer createBuffer(BufferType type, void* data, BufferUsage usage);
    };
}
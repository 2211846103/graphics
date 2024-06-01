#pragma once

#include <glad/glad.h>
#include <graphics_components.hpp>

namespace Graphics {
    // Boilerplate (Don't mind it)
    struct Texture {};
    struct Shader {};

    class Vertex {
        public:
            float position[3];
            Vertex (float x, float y, float z);
    };

    class GraphicsAPI {
        public:
            virtual void init();
            virtual Texture createTexture(char* path);
            virtual Shader createShader(char* vertexSource, char* fragmentSource);
            virtual Buffer createBuffer(BufferType type, void* data, BufferUsage usage);
            virtual VertexArray createVertexArray(Vertex* vertices);
            virtual void draw(VertexArray& vertexArray, Shader& shader, Texture& texture);
    };

    class OpenGLGraphics: public GraphicsAPI {
        public:
            void init(int x, int y, int width, int height);
            Buffer createBuffer(BufferType type, void* data, BufferUsage usage);
            VertexArray createVertexArray(Vertex* vertices);
            void draw(VertexArray& vertexArray, Shader& shader, Texture& texture);
    };
}
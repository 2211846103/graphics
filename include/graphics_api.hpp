#pragma once

#include <glad/glad.h>
#include <window.hpp>
#include <graphics_components.hpp>
#include <shader.hpp>

namespace Graphics {
    // Boilerplate (Don't mind it)
    struct Texture {};

    class Vertex {
        public:
            float position[3];
            Vertex (float x, float y, float z);
    };

    class GraphicsAPI {
        public:
            virtual void init(Window &window) {};
            virtual Texture createTexture(char* path) {};
            virtual Shader createShader(char* vertexSource, char* fragmentSource) {};
            virtual Buffer createBuffer(BufferType type, void* data, BufferUsage usage) {};
            virtual VertexArray createVertexArray(Vertex* vertices) = 0;
            virtual void draw(VertexArray& vertexArray, Shader& shader, Texture& texture) {};
    };

    class OpenGLGraphics: public GraphicsAPI {
        public:
            void init(Window &window);
            Buffer createBuffer(BufferType type, void* data, BufferUsage usage);
            VertexArray createVertexArray(Vertex* vertices);
            void draw(VertexArray& vertexArray, Shader& shader, Texture& texture);
    };
}
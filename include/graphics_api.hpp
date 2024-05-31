#pragma once

#include <glad/glad.h>
#include <window.hpp>

#include <graphics_components.hpp>
#include <shader.hpp>

namespace Graphics {
    // Boilerplate (Don't mind it)
    struct Texture {};
    struct VertexArray {};

    class GraphicsApi {
        public:
            virtual void init(Window &window);
            virtual Texture createTexture(char* path);
            virtual Shader createShader(char* vertexSource, char* fragmentSource);
            virtual Buffer createBuffer(void* data);
            virtual VertexArray createVertexArray();
            virtual void Draw(VertexArray& vertexArray, Shader& shader, Texture& texture);
    };

    class OpenGLGraphics: public GraphicsApi {
        void init(Window &window);
    };
}
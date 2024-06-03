#pragma once

#include <memory>

#include <glad/glad.h>
#include <window.hpp>
#include <graphics_components.hpp>
#include <shader.hpp>

namespace Graphics {
    // Boilerplate (Don't mind it)
    struct Texture {};

    class GraphicsAPI {
        public:
            virtual void init(Window &window) = 0;
            virtual std::unique_ptr<Texture> createTexture(char* path) = 0;
            virtual std::unique_ptr<Shader> createShader(char* vertexSource, char* fragmentSource) = 0;
            virtual Buffer* createBuffer(BufferType type, void* data, BufferUsage usage) = 0;
            virtual std::unique_ptr<VertexArray> createVertexArray(float* vertices, int vertexCount) = 0;
            virtual void draw(VertexArray* vertexArray, Shader& shader, Texture& texture) = 0;
    };

    class OpenGLGraphics: public GraphicsAPI {
        public:
            void init(Window &window) override;
            std::unique_ptr<Texture> createTexture(char* path) override;
            std::unique_ptr<Shader> createShader(char* vertexSource, char* fragmentSource) override;
            Buffer* createBuffer(BufferType type, void* data, BufferUsage usage) override;
            std::unique_ptr<VertexArray> createVertexArray(float* vertices, int vertexCount) override;
            void draw(VertexArray* vertexArray, Shader& shader, Texture& texture) override;
    };
}
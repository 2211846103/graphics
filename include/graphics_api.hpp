#pragma once

#include <glad/glad.h>
#include <window.hpp>
#include <shader.hpp>
#include <graphics_components.hpp>
#include <texture.hpp>

namespace Graphics {
    // Abstract Factory
    class GraphicsAPI {
        public:
            virtual ~GraphicsAPI() = default;

            virtual Buffer* createBuffer(BufferType type, void* data, size_t size, BufferUsage usage) = 0;
            virtual Shader* createShader(const char* vPath, const char* fPath) = 0;
            virtual VertexArray* createVertexArray(Vertex* vertices, size_t size) = 0;
            virtual Texture2D* createTexture2D(const char* path) = 0;
            virtual Texture3D* createTexture3D(const char* path[], size_t size = 0) = 0;
            virtual TextureCube* createTextureCube(const char* path[], size_t size = 0) = 0;
    };

    // Concrete Factories
    class OpenGLGraphicsAPI : public GraphicsAPI {
        public:
            OpenGLGraphicsAPI(Window& window);
            Buffer* createBuffer(BufferType type, void* data, size_t size, BufferUsage usage) override;
            Shader* createShader(const char* vPath, const char* fPath) override;
            VertexArray* createVertexArray(Vertex* vertices, size_t size) override;
            Texture2D* createTexture2D(const char* path) override;
            Texture3D* createTexture3D(const char* path[], size_t size = 0) override;
            TextureCube* createTextureCube(const char* path[], size_t size = 0) override;
    };
}
#pragma once

#include <glad/glad.h>
#include <window.hpp>
#include <shader.hpp>
#include <graphics_components.hpp>
#include <texture.hpp>

namespace Graphics {
    using namespace Math;
    // Abstract Factory
    class GraphicsAPI {
        private:
            int _width, _height;

        public:
            virtual ~GraphicsAPI() = default;

            virtual Buffer* createBuffer(BufferType type, void* data, size_t size, BufferUsage usage) = 0;
            virtual Shader* createShader(const char* vPath, const char* fPath) = 0;
            virtual VertexArray* createVertexArray() = 0;
            virtual Texture2D* createTexture2D(const char* path) = 0;
            virtual Texture2D* createTexture2D(Vec4 color) = 0;
            virtual Texture3D* createTexture3D(const char* path[], size_t size = 0) = 0;
            virtual TextureCube* createTextureCube(const char* path[], size_t size = 0) = 0;

            virtual void enableZBuffer() = 0;
            virtual void setClearColor(Vec3 color) = 0;
            virtual void clear() = 0;

            void getDimensions(int* width, int* height);
    };

    // Concrete Factories
    class OpenGLGraphicsAPI : public GraphicsAPI {
        private:
            Vec3 _color;
            GLenum _channelBuffers = GL_COLOR_BUFFER_BIT;

        public:
            OpenGLGraphicsAPI(Window& window);
            Buffer* createBuffer(BufferType type, void* data, size_t size, BufferUsage usage) override;
            Shader* createShader(const char* vPath, const char* fPath) override;
            VertexArray* createVertexArray() override;
            Texture2D* createTexture2D(const char* path) override;
            Texture2D* createTexture2D(Vec4 color) override;
            Texture3D* createTexture3D(const char* path[], size_t size = 0) override;
            TextureCube* createTextureCube(const char* path[], size_t size = 0) override;

            void enableZBuffer() override;
            void setClearColor(Vec3 color) override;
            void clear() override;
    };
}
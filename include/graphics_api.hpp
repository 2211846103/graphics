#pragma once

#include <glad/glad.h>
#include <window.hpp>
#include <shader.hpp>
#include <graphics_components.hpp>

namespace Graphics {
    // Abstract Factory
    class GraphicsAPI {
        public:
            virtual ~GraphicsAPI() = default;

            virtual Buffer* createBuffer(BufferType type, void* data, BufferUsage usage) = 0;
            virtual Shader* createShader(const char* vPath, const char* fPath) = 0;
    };

    // Concrete Factories
    class OpenGLGraphicsAPI : public GraphicsAPI {
        public:
            OpenGLGraphicsAPI(Window& window);
            Buffer* createBuffer(BufferType type, void* data, BufferUsage usage) override;
            Shader* createShader(const char* vPath, const char* fPath) override;
    };
}
#pragma once

#include <graphics_components.hpp>
#include <graphics_api.hpp>
#include <shader.hpp>
#include <texture.hpp>

namespace Engine {
    class Component {
        public:
            virtual void init() = 0;
            virtual void update(float dt) = 0;
            virtual void render() = 0;
    };

    class Material : public Component {
        private:
            Graphics::GraphicsAPI* _api;
            Graphics::Shader* _shader;
            Graphics::Texture* _albedo = nullptr;
        public:
            unsigned char unit = 0;

            Material(Graphics::GraphicsAPI* api);

            void setShader(const char* vertexPath, const char* fragmentPath);
            void setAlbedo(const char* path);

            void init() override;
            void update(float dt) override;
            void render() override;
    };

    class Mesh : public Component {
        private:
            Graphics::GraphicsAPI* _api;
            Graphics::VertexArray* _vao;
        public:
            Mesh(Graphics::GraphicsAPI* api);

            void setVertices(Graphics::Vertex* vertices, size_t size);
            void setIndices(int* indices, size_t size);

            void init() override;
            void update(float dt) override;
            void render() override;
    };
}
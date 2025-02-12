#pragma once

#include <graphics_components.hpp>
#include <graphics_api.hpp>
#include <shader.hpp>
#include <texture.hpp>
#include <math.hpp>

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

        public:
            unsigned char unit = 0;
            Graphics::Shader* shader;
            Graphics::Texture* albedo = nullptr;

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

    class Renderer : public Component {
        private:
            std::unique_ptr<Graphics::GraphicsAPI> _api;

        public:
            std::unique_ptr<Mesh> mesh;
            std::unique_ptr<Material> material;
            std::unique_ptr<Graphics::Shader> shader;

            Renderer(Graphics::GraphicsAPI* api);

            void setShader(const char* vPath, const char* fPath);

            void init() override;
            void update(float dt) override;
            void render() override;
    };
}
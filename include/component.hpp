#pragma once

#include <graphics_components.hpp>
#include <graphics_api.hpp>
#include <shader.hpp>
#include <texture.hpp>
#include <math.hpp>

namespace Engine {
    using namespace Graphics;

    class Component {
        protected:
            GraphicsAPI* _api;

        public:
            virtual void init() = 0;
            virtual void update(float dt) = 0;
            virtual void render() = 0;
    };

    class Material : public Component {
        public:
            unsigned char unit = 0;
            Texture* albedo = nullptr;

            Material(GraphicsAPI* api);
            ~Material();

            void setAlbedo(const char* path);

            void init() override;
            void update(float dt) override;
            void render() override;
    };

    class Mesh : public Component {
        private:
            VertexArray* _vao;
            
        public:
            Mesh(GraphicsAPI* api);
            ~Mesh();

            void setVertices(Vertex* vertices, size_t size);
            void setIndices(int* indices, size_t size);

            void init() override;
            void update(float dt) override;
            void render() override;
    };

    class Renderer : public Component {
        public:
            Mesh* mesh;
            Material* material;
            Shader* shader;

            Renderer(GraphicsAPI* api);
            ~Renderer();

            void setShader(const char* vPath, const char* fPath);

            void init() override;
            void update(float dt) override;
            void render() override;
    };

    class Transform : public Component {
        public:
            Math::Mat4 model;
            Math::Mat4 view;
            Math::Mat4 projection;

            Transform(GraphicsAPI* api);
            ~Transform();

            void init() override;
            void update(float dt) override;
            void render() override;
    };
}
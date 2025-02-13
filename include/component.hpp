#pragma once

#include <graphics_components.hpp>
#include <graphics_api.hpp>
#include <shader.hpp>
#include <texture.hpp>
#include <math.hpp>
#include <material.hpp>

namespace Engine {
    using namespace Graphics;
    using namespace Math;

    class Component {
        public:
            virtual void init() {};
            virtual void update(float dt) {};
            virtual void render() {};
    };

    class Mesh : public Component {
        private:
            VertexArray* _vao;
            GraphicsAPI* _api;
            
        public:
            Material* material;

            Mesh(GraphicsAPI* api);
            ~Mesh();

            void setVertices(Vertex* vertices, size_t size);
            void setIndices(int* indices, size_t size);

            void render() override;
    };

    class Renderer : public Component {
        private:
            GraphicsAPI* _api;

        public:
            Mesh* mesh;
            Shader* shader;

            Renderer(GraphicsAPI* api);
            ~Renderer();

            void setShader(const char* vPath, const char* fPath);

            void render() override;
    };

    class Transform : public Component {
        private:
            Mat4 _model;

        public:
            Vec3 position;
            Vec3 rotation;
            Vec3 scale;

            void update(float dt) override;
    };

    class Camera : public Component {
        private:
            Mat4 _view;
            Mat4 _projection;
        public:
            Vec3 position;

            void update(float dt) override;
    };
}
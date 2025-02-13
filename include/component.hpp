#pragma once

#include <graphics_components.hpp>
#include <shader.hpp>
#include <texture.hpp>
#include <math.hpp>
#include <material.hpp>
#include <scene.hpp>

namespace Engine {
    using namespace Graphics;

    class Component {
        public:
            GameObject* gameObject;

            Component(GameObject* obj);
            virtual ~Component() = default;

            virtual void init() {};
            virtual void update(float dt) {};
            virtual void render() {};
    };

    class Mesh : public Component {
        private:
            VertexArray* _vao;
            
        public:
            Material* material;

            Mesh(GameObject* obj);
            ~Mesh();

            void setVertices(Vertex* vertices, size_t size);
            void setIndices(int* indices, size_t size);

            void render() override;
    };

    class Renderer : public Component {
        public:
            Shader* shader;

            Renderer(GameObject* obj);
            ~Renderer();

            void setShader(const char* vPath, const char* fPath);

            void update(float dt) override;
            void render() override;
    };

    class Transform : public Component {
        private:
            Mat4 _model;

        public:
            Vec3 position{0, 0, 0};
            Vec3 rotation{0, 0, 0};
            Vec3 scale{1, 1, 1};

            Transform(GameObject* obj);

            Mat4& getModel();

            void update(float dt) override;
    };
}
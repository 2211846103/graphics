#pragma once

#include <graphics_components.hpp>
#include <shader.hpp>
#include <texture.hpp>
#include <math.hpp>
#include <material.hpp>
#include <scene.hpp>

namespace Engine {
    using namespace Graphics;
    using namespace Math;

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
            Shader* shader = nullptr;

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

    class Camera : public Component {
        private:
            Mat4 _view;
            Mat4 _projection;
            Vec3 _target;

            void viewUpdate();
            void projectionUpdate();

        public:
            Vec3 direction;
            Vec3 right;
            Vec3 up;
            Vec3 front;

            float fov = 45;
            float aspect = 16 / 9.0;
            float near = 0.1;
            float far = 100;

            Camera(GameObject* obj);

            Mat4& getView();
            Mat4& getProjection();
            
            void update(float dt) override;
    };

    class Light : public Component {
        public:
            Vec3 ambient;
            Vec3 diffuse;
            Vec3 specular;

            Light(GameObject* obj);
    };
}
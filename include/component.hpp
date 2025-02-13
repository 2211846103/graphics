#pragma once

#include <unordered_map>
#include <typeinfo>

#include <graphics_components.hpp>
#include <graphics_api.hpp>
#include <shader.hpp>
#include <texture.hpp>
#include <math.hpp>
#include <material.hpp>

namespace Engine {
    using namespace Graphics;
    using namespace Math;

    class GameObject;

    class Component {
        public:
            GameObject* gameObject;

            Component(GameObject* obj);
            virtual ~Component() = default;

            virtual void init() {};
            virtual void update(float dt) {};
            virtual void render() {};
    };

    class GameObject {
        private:
        std::unordered_map<const char*, Component*> _components;
        
        public:
            GraphicsAPI* api;

            GameObject(GraphicsAPI* api);
            ~GameObject();

            template <typename T>
            void addComponent() {
                const char* name = typeid(T).name();
                if (_components.find(name) != _components.end()) return;
                _components[name] = new T(this);
            }
            template <typename T>
            T* getComponent() {
                auto it = _components.find(typeid(T).name());
                return (it != _components.end()) ? dynamic_cast<T*>(it->second) : nullptr;
            }
            template <typename T>
            void removeComponent() {
                auto it = _components.find(typeid(T).name());
                if (it == _components.end()) return;
                delete it ->second;
                _components.erase(it);
            }

            void init();
            void update(float dt);
            void render();
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

    class Camera : public Component {
        private:
            Mat4 _view;
            Mat4 _projection;
        public:
            Vec3 position;

            void update(float dt) override;
    };
}
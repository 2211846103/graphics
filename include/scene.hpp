#pragma once

#include <unordered_map>
#include <typeinfo>

#include <graphics_api.hpp>

namespace Engine {
    using namespace Graphics;

    class Component;
    class Renderer;

    class GameObject {
        private:
        std::unordered_map<const char*, Component*> _components;
        
        public:
            const int id;
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

    class Scene {
        private:
            GameObject* _activeCamera;
            std::vector<GameObject*> _gameObjects;

        public:
            ~Scene();

            GameObject* getActiveCamera();
            void setCameraActive(GameObject* camera);

            GameObject* createGameObject();
            GameObject* getGameObjectByID(int id);

            void initGameObjects();
            void updateGameObjects(float dt);
            void renderGameObjects();
    };

    class SceneManager {
        private:
            static std::vector<Scene*> _scenes;
            static Scene* _currentScene;
        
        public:
            static GraphicsAPI* api;

            static void setGraphicsAPI(GraphicsAPI* api);

            static void setCurrentScene(Scene* scene);
            static Scene* getCurrentScene();

            static void initCurrentScene();
            static void updateCurrentScene(float dt);
            static void renderCurrentScene();
    };
}
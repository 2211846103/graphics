#pragma once

#include <unordered_map>
#include <typeinfo>

#include <component.hpp>

namespace Engine {
    using namespace Graphics;

    class GameObject {
        private:
            GraphicsAPI* _api;
            std::unordered_map<const char*, Component*> _components;
        
        public:
            GameObject(GraphicsAPI* api);
            ~GameObject();

            template <typename T>
            void addComponent() {
                const char* name = typeid(T).name();
                if (_components.find(name) != _components.end()) return;
                _components[name] = new T(this->_api);
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
}
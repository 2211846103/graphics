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
            template <typename T>
            void addComponent() {
                _components[typeid(T).name()] = new T(_api);
            }
    };
}
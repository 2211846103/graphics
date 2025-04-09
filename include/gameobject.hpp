#pragma once

#include <unordered_map>
#include <typeinfo>
#include <typeindex>

#include <graphics_api.hpp>

namespace Engine {
using namespace Graphics;

class Component;
class Renderer;

class GameObject {
private:
  std::unordered_map<std::type_index, Component*> _components;

public:
  const int id;

  GameObject();
  ~GameObject();

  template <typename T>
  void addComponent() {
    std::type_index index(typeid(T));
    if (_components.find(index) != _components.end()) return;
    _components[index] = new T(this);
  }
  template <typename T>
  T* getComponent() {
    for (auto& pair : _components) {
      if (T* casted = dynamic_cast<T*>(pair.second)) {
        return casted;
      }
    }
    return nullptr;
  }
  template <typename T>
  void removeComponent() {
    auto it = _components.find(std::type_index(typeid(T)));
    if (it == _components.end()) return;
    delete it ->second;
    _components.erase(it);
  }

  void init();
  void update(float dt);
  void render();
};
}

#include <game_object.hpp>

using namespace Engine;

GameObject::GameObject(GraphicsAPI* api) : _api{api} {}

GameObject::~GameObject() {
    for (auto& pair : _components) {
        delete pair.second;
    }
    _components.clear();
}

void GameObject::init() {}
void GameObject::update(float dt) {}
void GameObject::render() {
    Renderer* r = this->getComponent<Renderer>();
    if (!r) return;
    r->render();
}
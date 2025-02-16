#include <gameobject.hpp>
#include <component.hpp>

using namespace Engine;

static int gameobject_next_id = 0;

GameObject::GameObject(GraphicsAPI* api) : api{api}, id{gameobject_next_id++} {
    this->addComponent<Transform>();
}

GameObject::~GameObject() {
    for (auto& pair : _components) {
        delete pair.second;
    }
    _components.clear();
}

void GameObject::init() {
    for (auto& pair : _components) {
        pair.second->init();
    }
}

void GameObject::update(float dt) {
    for (auto& pair : _components) {
        pair.second->update(dt);
    }
}

void GameObject::render() {
    Renderer* r = this->getComponent<Renderer>();
    if (!r) return;
    r->render();
}
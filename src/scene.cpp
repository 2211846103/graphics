#include <scene.hpp>

using namespace Engine;

static int gameobject_next_id = 0;

GraphicsAPI* Engine::SceneManager::api = nullptr;
Scene* Engine::SceneManager::_currentScene = nullptr;

Scene::~Scene() {
    for (GameObject* obj : _gameObjects) {
        delete obj;
    }
    _gameObjects.clear();
}

GameObject* Scene::getActiveCamera() {
    return this->_activeCamera;
}

void Scene::setCameraActive(GameObject* camera) {
    this->_activeCamera = camera;
}

GameObject* Scene::createGameObject() {
    GameObject* obj = new GameObject(SceneManager::api);
    _gameObjects.push_back(obj);
    return obj;
}

GameObject* Scene::getGameObjectByID(int id) {
    for (GameObject* obj : _gameObjects) {
        if (obj->id != id) continue;
        return obj;
    }
    return nullptr;
}

void Scene::initGameObjects() {
    for (GameObject* obj : _gameObjects) {
        obj->init();
    }
}
void Scene::updateGameObjects(float dt) {
    for (GameObject* obj : _gameObjects) {
        obj->update(dt);
    }
}
void Scene::renderGameObjects() {
    for (GameObject* obj : _gameObjects) {
        obj->render();
    }
}

void SceneManager::setGraphicsAPI(GraphicsAPI* api) {
    SceneManager::api = api;
}

void SceneManager::setCurrentScene(Scene* scene) {
    SceneManager::_currentScene = scene;
}

Scene* SceneManager::getCurrentScene() {
    return SceneManager::_currentScene;
}

void SceneManager::initCurrentScene() {
    SceneManager::_currentScene->initGameObjects();
}

void SceneManager::updateCurrentScene(float dt) {
    SceneManager::_currentScene->updateGameObjects(dt);
}

void SceneManager::renderCurrentScene() {
    SceneManager::_currentScene->initGameObjects();
}
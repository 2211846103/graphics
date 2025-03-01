#include <scene.hpp>
#include <mesh.hpp>

using namespace Engine;

static int gameobject_next_id = 0;

GraphicsAPI* Engine::SceneManager::api = nullptr;
Scene* Engine::SceneManager::_currentScene = nullptr;

Scene::~Scene() {
    for (GameObject* obj : _gameObjects) {
        delete obj;
    }
    _gameObjects.clear();
    _lights.clear();
}

GameObject* Scene::getGameObjectByID(int id) {
    for (GameObject* obj : _gameObjects) {
        if (obj->id != id) continue;
        return obj;
    }
    return nullptr;
}

GameObject* Scene::createGameObject() {
    GameObject* obj = new GameObject(SceneManager::api);
    _gameObjects.push_back(obj);
    return obj;
}

GameObject* Scene::createPlane() {
    GameObject* obj = new GameObject(SceneManager::api);
    obj->addComponent<PlaneMesh>();
    obj->addComponent<Renderer>();

    _gameObjects.push_back(obj);
    return obj;
}

GameObject* Scene::createCube() {
    GameObject* obj = new GameObject(SceneManager::api);
    obj->addComponent<CubeMesh>();
    obj->addComponent<Renderer>();

    _gameObjects.push_back(obj);
    return obj;
}

GameObject* Scene::createSphere() {
    GameObject* obj = new GameObject(SceneManager::api);
    obj->addComponent<SphereMesh>();
    obj->addComponent<Renderer>();

    _gameObjects.push_back(obj);
    return obj;
}

GameObject* Scene::createLight() {
    GameObject* obj = new GameObject(SceneManager::api);
    obj->addComponent<Transform>();
    obj->addComponent<Light>();

    _gameObjects.push_back(obj);
    return obj;
}

GameObject* Scene::createOrthoCamera() {
    GameObject* obj = new GameObject(SceneManager::api);
    obj->addComponent<OrthographicCamera>();

    _gameObjects.push_back(obj);
    return obj;
}

GameObject* Scene::createPersCamera() {
    GameObject* obj = new GameObject(SceneManager::api);
    obj->addComponent<PerspectiveCamera>();

    _gameObjects.push_back(obj);
    return obj;
}

GameObject* Scene::getActiveCamera() {
    return this->_activeCamera;
}

void Scene::setCameraActive(GameObject* camera) {
    this->_activeCamera = camera;
}

std::vector<GameObject*> Scene::getLights() {
    std::vector<GameObject*> lights;
    for (auto& obj : _gameObjects) {
        Light* lightComp = obj->getComponent<Light>();
        if (lightComp) lights.push_back(obj);
    }
    return lights;
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
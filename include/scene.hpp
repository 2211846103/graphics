#pragma once

#include <gameobject.hpp>

namespace Engine {
    using namespace Graphics;
    class Scene {
        private:
            GameObject* _activeCamera;
            std::vector<GameObject*> _gameObjects;
            std::vector<GameObject*> _lights;

        public:
            Scene() = default;
            ~Scene();

            GameObject* getGameObjectByID(int id);

            GameObject* createGameObject();
            GameObject* createCube();
            GameObject* createPlane();
            GameObject* createSphere();
            GameObject* createLight();
            
            GameObject* createCamera();
            GameObject* getActiveCamera();
            void setCameraActive(GameObject* camera);
            
            std::vector<GameObject*> getLights();

            void initGameObjects();
            void updateGameObjects(float dt);
            void renderGameObjects();
    };

    class SceneManager {
        private:
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
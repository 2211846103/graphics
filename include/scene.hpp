#pragma once

#include <gameobject.hpp>

namespace Engine {
    using namespace Graphics;
    class Scene {
        private:
            GameObject* _activeCamera;
            std::vector<GameObject*> _gameObjects;

        public:
            ~Scene();

            GameObject* getGameObjectByID(int id);

            GameObject* createGameObject();
            GameObject* createCube();
            GameObject* createPlane();
            
            GameObject* createCamera();
            GameObject* getActiveCamera();
            void setCameraActive(GameObject* camera);
            

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
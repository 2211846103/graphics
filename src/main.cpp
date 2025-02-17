// Includes
#include <window.hpp>
#include <mesh.hpp>
#include <Input.hpp>
#include <ctime>

using namespace Graphics;
using namespace Engine;
using namespace Math;

// Main code
int main(int argc, char* argv[]) {
    // Preperations
    Window window(800, 600, "test");
    Input::init(&window, CursorDisabled);
    OpenGLGraphicsAPI graphics(window);
    graphics.enableZBuffer();
    graphics.setClearColor({0.2, 0.2, 0.2});
    SceneManager::setGraphicsAPI(&graphics);
    Scene mainScene;
    SceneManager::setCurrentScene(&mainScene);

    // Code
    Vec3 cubePositions[] = {
        { 0.0f,  0.0f,  0.0f },
        { 2.0f,  5.0f, -15.0f },
        { -1.5f, -2.2f, -2.5f },
        { -3.8f, -2.0f, -12.3f },
        { 2.4f, -0.4f, -3.5f },
        { -1.7f,  3.0f, -7.5f },
        { 1.3f, -2.0f, -2.5f },
        { 1.5f,  2.0f, -2.5f },
        { 1.5f,  0.2f, -1.5f },
        { -1.3f,  1.0f, -1.5f }
    };    
    for (int i = 0; i < 10; i++) {
        // Cubes to render
        GameObject* cube = mainScene.createPlane();

        // This Line is not Necessary anymore
        cube->getComponent<Mesh>()->material->setAlbedo("../res/images/test.jpg");

        Transform* transform = cube->getComponent<Transform>();
        transform->position = cubePositions[i];
        transform->rotation = Vec3(10 * i, 15 * i, 20 * i);
    }

    // Camera
    GameObject* cameraObj = mainScene.createCamera();
    mainScene.setCameraActive(cameraObj);

    Camera* camera = cameraObj->getComponent<Camera>();
    Transform* cameraTrans = cameraObj->getComponent<Transform>();
    cameraTrans->position = Vec3(0, 0, -15);

    // Calculating DeltaTime
    float dt = 0;
    const float cameraSpeed = 10;
    
    mainScene.initGameObjects();
    while (!window.shouldClose()) {
        graphics.clear();

        if (Input::isKeyPressed(W)) cameraTrans->position -= dt * cameraSpeed * camera->front.data;
        if (Input::isKeyPressed(S)) cameraTrans->position += dt * cameraSpeed * camera->front.data;
        if (Input::isKeyPressed(A)) cameraTrans->position += dt * cameraSpeed * (camera->front.cross(camera->up)).normalize().data;
        if (Input::isKeyPressed(D)) cameraTrans->position -= dt * cameraSpeed * (camera->front.cross(camera->up)).normalize().data;
        if (Input::isKeyPressed(LSHIFT)) cameraTrans->position -= dt * cameraSpeed * camera->up.data;
        if (Input::isKeyPressed(SPACE)) cameraTrans->position += dt * cameraSpeed * camera->up.data;


        mainScene.updateGameObjects(dt);
        mainScene.renderGameObjects();

        dt = window.update();
    }

    // Cleans/Deletes all GLFW resources that we allocated.
    glfwTerminate();
    return 0;
}
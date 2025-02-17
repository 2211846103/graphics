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
    for (int i = 0; i < 0; i++) {
        // Cubes to render
        GameObject* cube = mainScene.createCube();

        // This Line is not Necessary anymore
        cube->getComponent<Mesh>()->material->setAlbedo("../res/images/test.jpg");

        Transform* transform = cube->getComponent<Transform>();
        transform->position = cubePositions[i];
        transform->rotation = Vec3(10 * i, 15 * i, 20 * i);
    }

    Vec3 objectColor = {1.0f, 0.5f, 0.31f};
    Vec3 lightColor = {1.0f, 1.0f, 1.0f};
    Vec3 lightPos = {1.2f, 1.0f, 2.0f};

    GameObject* cube = mainScene.createCube();
    cube->getComponent<Transform>()->position = Vec3(0, 0, 0);
    cube->getComponent<Renderer>()->shader->setUniform("objectColor", objectColor);
    cube->getComponent<Renderer>()->shader->setUniform("lightColor", lightColor);

    GameObject* light = mainScene.createCube();
    light->getComponent<Transform>()->position = lightPos;
    light->getComponent<Transform>()->scale = Vec3(0.2, 0.2, 0.2);
    light->getComponent<Renderer>()->shader->setUniform("objectColor", lightColor);
    light->getComponent<Renderer>()->shader->setUniform("lightColor", lightColor);

    // Camera
    GameObject* cameraObj = mainScene.createCamera();
    mainScene.setCameraActive(cameraObj);

    Camera* camera = cameraObj->getComponent<Camera>();
    Transform* cameraTrans = cameraObj->getComponent<Transform>();
    cameraTrans->position = Vec3(0, 0, -15);

    // Calculating DeltaTime
    float dt = 0;
    const float cameraSpeed = 10;
    float mouseSensitivity = 0.1f;
    float lastX = 400, lastY = 300;
    float xoffset, yoffset;

    
    mainScene.initGameObjects();
    while (!window.shouldClose()) {
        graphics.clear();
        
        if (Input::isKeyPressed(W)) cameraTrans->position -= dt * cameraSpeed * camera->front.data;
        if (Input::isKeyPressed(S)) cameraTrans->position += dt * cameraSpeed * camera->front.data;
        if (Input::isKeyPressed(A)) cameraTrans->position += dt * cameraSpeed * (camera->front.cross(camera->up)).normalize().data;
        if (Input::isKeyPressed(D)) cameraTrans->position -= dt * cameraSpeed * (camera->front.cross(camera->up)).normalize().data;
        if (Input::isKeyPressed(LSHIFT)) cameraTrans->position -= dt * cameraSpeed * camera->up.data;
        if (Input::isKeyPressed(SPACE)) cameraTrans->position += dt * cameraSpeed * camera->up.data;
        
        Vec2 mousePos = Input::getMousePosition();
        Vec3 direction;
        
        xoffset = mousePos.data.x - lastX;
        yoffset = mousePos.data.y - lastY;
        lastX = mousePos.data.x;
        lastY = mousePos.data.y;

        xoffset *= mouseSensitivity;
        yoffset *= mouseSensitivity;

        cameraTrans->rotation.data.x += yoffset;
        cameraTrans->rotation.data.y += xoffset;

        if (cameraTrans->rotation.data.x > 89.0f) cameraTrans->rotation.data.x = 89.0f;
        if (cameraTrans->rotation.data.x < -89.0f) cameraTrans->rotation.data.x = -89.0f;
        
        direction.data.x = cos(glm::radians(cameraTrans->rotation.data.y)) * cos(glm::radians(cameraTrans->rotation.data.x));
        direction.data.y = sin(glm::radians(cameraTrans->rotation.data.x));
        direction.data.z = sin(glm::radians(cameraTrans->rotation.data.y)) * cos(glm::radians(cameraTrans->rotation.data.x));
        camera->front = direction.normalize();


        mainScene.updateGameObjects(dt);
        mainScene.renderGameObjects();

        dt = window.update();
    }

    // Cleans/Deletes all GLFW resources that we allocated.
    glfwTerminate();
    return 0;
}
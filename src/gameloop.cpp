#include <gameloop.hpp>

using namespace Engine;

Scene mainScene = Scene();
Transform* cameraTrans;
Camera* camera;

const float cameraSpeed = 10;
float mouseSensitivity = 0.1f;
float lastX = 400, lastY = 300;
float xoffset, yoffset;

void Engine::Start() {
    SceneManager::setCurrentScene(&mainScene);

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
        GameObject* cube = mainScene.createCube();

        // This Line is not Necessary anymore
        cube->getComponent<Mesh>()->material->setAlbedo("../res/images/test.jpg");

        Transform* transform = cube->getComponent<Transform>();
        transform->position = cubePositions[i];
        transform->rotation = Vec3(10 * i, 15 * i, 20 * i);
    }

    GameObject* cameraObj = mainScene.createCamera();
    mainScene.setCameraActive(cameraObj);

    camera = cameraObj->getComponent<Camera>();
    cameraTrans = cameraObj->getComponent<Transform>();
    cameraTrans->position = Vec3(0, 0, -15);
}

void Engine::Update(float dt) {
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

    cameraTrans->rotation.data.x += xoffset;
    cameraTrans->rotation.data.y += yoffset;
    
    direction.data.x = cos(glm::radians(cameraTrans->rotation.data.x)) * cos(glm::radians(cameraTrans->rotation.data.y));
    direction.data.y = sin(glm::radians(cameraTrans->rotation.data.y));
    direction.data.z = sin(glm::radians(cameraTrans->rotation.data.x)) * cos(glm::radians(cameraTrans->rotation.data.y));
    camera->front = direction.normalize();
}
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
    OpenGLGraphicsAPI graphics(window);
    
    Input::init(&window, CursorDisabled);
    graphics.enableZBuffer();
    //graphics.setClearColor({0.2, 0.2, 0.2});

    SceneManager::setGraphicsAPI(&graphics);
    Scene mainScene;
    SceneManager::setCurrentScene(&mainScene);

    /*
    std::vector<int> data(1024, 0);
    ComputeShader* computeShader = graphics.createComputeShader("../res/shaders/light_compute.comp");
    Buffer* buffer = graphics.createBuffer(ShaderStorageBuffer, data.data(), data.size() * sizeof(int), DynamicCopy);
    buffer->setBindingPoint(0);
    computeShader->dispatch((data.size() * 63) / 64);
    int* newData = new int[data.size()];
    buffer->getData(newData, data.size() * sizeof(int));
    for (int i = 0; i < data.size(); i++) {
        std::cout << newData[i] << std::endl;
    }
    delete newData;
    delete buffer;
    delete computeShader;
    */

    Vec3 cameraPos = {0, 1, 2};
    GameObject* sphere = mainScene.createSphere();
    sphere->getComponent<Transform>()->position = {1, -1, 2};
    GameObject* light = mainScene.createLight();

    // Camera
    GameObject* cameraObj = mainScene.createCamera();
    mainScene.setCameraActive(cameraObj);
    Camera* camera = cameraObj->getComponent<Camera>();
    Transform* cameraTrans = cameraObj->getComponent<Transform>();
    cameraTrans->position = cameraPos;

    // Calculating DeltaTime
    float dt = 0;
    const float cameraSpeed = 3;
    float mouseSensitivity = 0.1f;
    float lastX = 0, lastY = 300;
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
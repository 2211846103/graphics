// Includes
#include <shader.hpp>
#include <window.hpp>
#include <graphics_api.hpp>
#include <component.hpp>
#include <ctime>
#include <Input.hpp>

using namespace Graphics;
using namespace Engine;
using namespace Math;

// Main code
int main(int argc, char* argv[]) {
    Window window(800, 600, "test");
    float aspectRatio = window.width / (float)window.height;

    OpenGLGraphicsAPI graphics(window);
    graphics.enableZBuffer();
    graphics.setClearColor({0.2, 0.2, 0.2});

    Input::init(&window);


    SceneManager::setGraphicsAPI(&graphics);
    Scene mainScene;
    SceneManager::setCurrentScene(&mainScene);

    Vertex vertices[] = {
        {{-0.5f, -0.5f, -0.5f},  {0.0f, 0.0f}},
        {{ 0.5f, -0.5f, -0.5f},  {1.0f, 0.0f}},
        {{ 0.5f,  0.5f, -0.5f},  {1.0f, 1.0f}},
        {{-0.5f,  0.5f, -0.5f},  {0.0f, 1.0f}},

        {{-0.5f, -0.5f,  0.5f},  {0.0f, 0.0f}},
        {{ 0.5f, -0.5f,  0.5f},  {1.0f, 0.0f}},
        {{ 0.5f,  0.5f,  0.5f},  {1.0f, 1.0f}},
        {{-0.5f,  0.5f,  0.5f},  {0.0f, 1.0f}},

        {{-0.5f,  0.5f,  0.5f},  {1.0f, 0.0f}},
        {{-0.5f,  0.5f, -0.5f},  {1.0f, 1.0f}},
        {{-0.5f, -0.5f, -0.5f},  {0.0f, 1.0f}},
        {{-0.5f, -0.5f,  0.5f},  {0.0f, 0.0f}},

        {{ 0.5f,  0.5f,  0.5f},  {1.0f, 0.0f}},
        {{ 0.5f,  0.5f, -0.5f},  {1.0f, 1.0f}},
        {{ 0.5f, -0.5f, -0.5f},  {0.0f, 1.0f}},
        {{ 0.5f, -0.5f,  0.5f},  {0.0f, 0.0f}},

        {{-0.5f, -0.5f, -0.5f},  {0.0f, 1.0f}},
        {{ 0.5f, -0.5f, -0.5f},  {1.0f, 1.0f}},
        {{ 0.5f, -0.5f,  0.5f},  {1.0f, 0.0f}},
        {{-0.5f, -0.5f,  0.5f},  {0.0f, 0.0f}},

        {{-0.5f,  0.5f, -0.5f},  {0.0f, 1.0f}},
        {{ 0.5f,  0.5f, -0.5f},  {1.0f, 1.0f}},
        {{ 0.5f,  0.5f,  0.5f},  {1.0f, 0.0f}},
        {{-0.5f,  0.5f,  0.5f},  {0.0f, 0.0f}}
    };

    int indices[] = {
         0,  1,  2,
         0,  2,  3,

         4,  5,  6,
         4,  6,  7,

         8,  9, 10,
         8, 10, 11,

        12, 13, 14,
        12, 14, 15,

        16, 17, 18,
        16, 18, 19,

        20, 21, 22,
        20, 22, 23
    };

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
    
    Material mat(&graphics);
    mat.setAlbedo("../res/images/test.jpg");

    for (int i = 0; i < 10; i++) {
        // Object to render
        GameObject* object = mainScene.createGameObject();

        object->addComponent<Mesh>();
        Mesh* mesh = object->getComponent<Mesh>();
        mesh->setVertices(vertices, sizeof(vertices));
        mesh->setIndices(indices, sizeof(indices));
        mesh->material = &mat;

        object->addComponent<Renderer>();
        Renderer* renderer = object->getComponent<Renderer>();
        renderer->setShader("../res/shaders/shader.vert", "../res/shaders/shader.frag");

        Transform* transform = object->getComponent<Transform>();
        transform->position = cubePositions[i];
        transform->rotation = Vec3(10 * i, 15 * i, 20 * i);
    }

    // Camera
    GameObject* cameraObj = mainScene.createGameObject();
    cameraObj->addComponent<Camera>();
    Camera* camera = cameraObj->getComponent<Camera>();
    camera->aspect = 800 / 600.0;

    mainScene.setCameraActive(cameraObj);
    Transform* cameraTrans = cameraObj->getComponent<Transform>();
    cameraTrans->position = Vec3(0, 0, -15);


    // Calculating DeltaTime
    float dt = 0;
    const float cameraSpeed = 30;

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
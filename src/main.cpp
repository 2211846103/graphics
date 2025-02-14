// Includes
#include <shader.hpp>
#include <window.hpp>
#include <graphics_api.hpp>
#include <component.hpp>
#include <ctime>

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

    GameObject* object = mainScene.createGameObject();

    Material mat(&graphics);

    object->addComponent<Mesh>();
    Mesh* mesh = object->getComponent<Mesh>();
    mesh->setVertices(vertices, sizeof(vertices));
    mesh->setIndices(indices, sizeof(indices));
    mesh->material = &mat;

    object->addComponent<Renderer>();
    Renderer* renderer = object->getComponent<Renderer>();
    renderer->setShader("../res/shaders/shader.vert", "../res/shaders/shader.frag");

    Transform* transform = object->getComponent<Transform>();
    transform->rotation.setX(45);
    transform->rotation.setY(45);

    
    mat.setAlbedo("../res/images/test2.jpg");
    
    object.addComponent<Mesh>();
    object.getComponent<Mesh>()->setVertices(vertices, sizeof(vertices));
    object.getComponent<Mesh>()->setIndices(indices, sizeof(indices));
    object.getComponent<Mesh>()->material = &mat;
    
    object.addComponent<Renderer>();
    object.getComponent<Renderer>()->setShader("../res/shaders/shader.vert", "../res/shaders/shader.frag");
    
    // Calculating DeltaTime
    float dt = 0;
    
    //object.getComponent<Transform>()->rotation.setX(45);
    
    // Camera and its properties
    object.addComponent<Camera>();

    mainScene.initGameObjects();
    while (!window.shouldClose()) {
        graphics.clear();

        mainScene.updateGameObjects(dt);
        mainScene.renderGameObjects();

    object.getComponent<Camera>()->radius = 3.0f;
    float objectRadius = object.getComponent<Camera>()->radius;
    // Set the camera position
    object.getComponent<Camera>()->up.setY(1.0f);
    object.getComponent<Camera>()->cameraTarget.setZ(-1.0f);

    object.getComponent<Camera>()->position.setZ(3.0f);
    // Set the perspective properties
    object.getComponent<Camera>()->fov = 45.0f;
    object.getComponent<Camera>()->aspect = aspectRatio;
    object.getComponent<Camera>()->near = 0.1f;
    object.getComponent<Camera>()->far = 100.0f;
    
    
    while (!window.shouldClose()) {
        graphics.clear();

        // Calculate the camera position
        float camX = sin(glfwGetTime()) * objectRadius;
        float camZ = cos(glfwGetTime()) * objectRadius;

        // Rotate the camera around the object
        //object.getComponent<Camera>()->position.setX(camX);
        //object.getComponent<Camera>()->position.setZ(camZ);
        
        object.update(dt);
        object.render();
        
        // Checks and call events and swap the buffers
        dt = window.update();

        object.getComponent<Camera>()->processInput(&window, dt);
        //window.processInput(&object, dt);
    }

    // Cleans/Deletes all GLFW resources that we allocated.
    glfwTerminate();
    return 0;
}
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
    OpenGLGraphicsAPI graphics(window);

    float aspectRatio = 800.0f / 600.0f;

    graphics.enableZBuffer();
    graphics.setClearColor({0.2, 0.2, 0.2});

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

    GameObject object(&graphics);
    Material mat(&graphics);
    mat.setAlbedo("../res/images/test2.jpg");

    object.addComponent<Mesh>();
    object.getComponent<Mesh>()->setVertices(vertices, sizeof(vertices));
    object.getComponent<Mesh>()->setIndices(indices, sizeof(indices));
    object.getComponent<Mesh>()->material = &mat;

    object.addComponent<Renderer>();
    object.getComponent<Renderer>()->setShader("../res/shaders/shader.vert", "../res/shaders/shader.frag");

    // Calculating DeltaTime
    float dt = 0;

    object.getComponent<Transform>()->rotation.setX(45);
    object.getComponent<Transform>()->rotation.setY(45);

    while (!window.shouldClose()) {
        graphics.clear();

        object.update(dt);
        object.render();

        // Checks and call events and swap the buffers
        dt = window.update();
    }

    // Cleans/Deletes all GLFW resources that we allocated.
    glfwTerminate();
    return 0;
}
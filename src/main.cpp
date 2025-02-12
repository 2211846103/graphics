// Includes
#include <shader.hpp>
#include <window.hpp>
#include <graphics_api.hpp>
#include <game_object.hpp>
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

    object.addComponent<Mesh>();
    object.getComponent<Mesh>()->setVertices(vertices, sizeof(vertices));
    object.getComponent<Mesh>()->setIndices(indices, sizeof(indices));

    object.addComponent<Material>();
    object.getComponent<Material>()->setAlbedo("../res/images/test.jpg");

    object.addComponent<Renderer>();
    object.getComponent<Renderer>()->setShader("../res/shaders/shader.vert", "../res/shaders/shader.frag");
    object.getComponent<Renderer>()->mesh = object.getComponent<Mesh>();
    object.getComponent<Renderer>()->material = object.getComponent<Material>();

    // Calculating DeltaTime
    float dt = 0;

    Math::Mat4 model = Math::Mat4::identity();
    Math::Mat4 view = Math::Mat4::identity();
    Math::Mat4 projection = Math::Mat4::identity();

    model = Math::Mat4::translation(view, Math::Vec3(0, 0, -2.5));
    projection = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);

    Renderer* rend = object.getComponent<Renderer>();

    while (!window.shouldClose()) {
        graphics.clear();

        model = Mat4::rotation(model, dt, Vec3(0.5, 1, 0));

        rend->shader->setUniform("model", model);
        rend->shader->setUniform("view", view);
        rend->shader->setUniform("projection", projection);
        object.render();

        // Checks and call events and swap the buffers
        dt = window.update();
    }

    // Cleans/Deletes all GLFW resources that we allocated.
    glfwTerminate();
    return 0;
}
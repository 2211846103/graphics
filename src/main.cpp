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

    Vertex vertices[] = {
        {{-0.5, -0.5, 0.0}, {0.0, 0.0}},
        {{ 0.5, -0.5, 0.0}, {1.0, 0.0}},
        {{-0.5,  0.5, 0.0}, {0.0, 1.0}},
        {{ 0.5,  0.5, 0.0}, {1.0, 1.0}}
    };

    int indices[] = {
        0, 1, 3,
        0, 3, 2
    };

    GameObject object(&graphics);

    object.addComponent<Mesh>();
    object.getComponent<Mesh>()->setVertices(vertices, sizeof(vertices));
    object.getComponent<Mesh>()->setIndices(indices, sizeof(indices));

    object.addComponent<Material>();
    object.getComponent<Material>()->setAlbedo("../res/images/test2.jpg");

    object.addComponent<Renderer>();
    object.getComponent<Renderer>()->setShader("../res/shaders/shader.vert", "../res/shaders/shader.frag");
    object.getComponent<Renderer>()->mesh = object.getComponent<Mesh>();
    object.getComponent<Renderer>()->material = object.getComponent<Material>();

    // Calculating DeltaTime
    float dt = 0;

    Math::Mat4 model = Math::Mat4::identity();
    Math::Mat4 view = Math::Mat4::identity();
    Math::Mat4 projection = Math::Mat4::identity();

    model = Math::Mat4::translation(view, Math::Vec3(0, -0.5, -3));
    model = Math::Mat4::rotation(model, glm::radians(-55.0f), Math::Vec3(1, 0, 0));
    projection = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);

    Renderer* rend = object.getComponent<Renderer>();

    while (!window.shouldClose()) {
        window.clear(0.2, 0.2, 0.2);



        rend->shader->setUniform("model", model);
        rend->shader->setUniform("view", view);
        rend->shader->setUniform("projection", projection);
        rend->render();

        // Checks and call events and swap the buffers
        dt = window.update();
    }

    // Cleans/Deletes all GLFW resources that we allocated.
    glfwTerminate();
    return 0;
}
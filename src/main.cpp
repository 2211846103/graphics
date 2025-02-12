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

    Mat4 model = Mat4::identity();

    while (!window.shouldClose()) {
        window.clear(0.2, 0.2, 0.2);

        model = Mat4::rotation(model, dt, Vec3(0, 0, 1));

        object.render();

        // Checks and call events and swap the buffers
        dt = window.update();
    }

    // Cleans/Deletes all GLFW resources that we allocated.
    glfwTerminate();
    return 0;
}
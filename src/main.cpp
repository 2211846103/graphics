// Includes
#include <window.hpp>
#include <graphics_api.hpp>
#include <engine.hpp>
#include <ctime>

using namespace Graphics;

// Main code
int main(int argc, char* argv[]) {
    Window window(800, 600, "test");

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

    Engine::Component::graphicsAPI = new OpenGLGraphicsAPI(window);

    Engine::Mesh mesh;
    mesh.setVertices(vertices, sizeof(vertices));
    mesh.setIndices(indices, sizeof(indices));

    Engine::Material material;
    material.setShader("../res/shaders/shader.vert", "../res/shaders/shader.frag");
    material.setAlbedo("../res/images/test2.jpg");

    // Calculating DeltaTime
    int lastTick = clock();
    float dt = 0;

    while (!window.shouldClose()) {
        dt = 1.0 / (clock() - lastTick);

        window.clear(0.2, 0.2, 0.2);

        material.update(dt);
        mesh.render();

        // Checks and call events and swap the buffers
        window.update();
    }

    // Cleans/Deletes all GLFW resources that we allocated.
    glfwTerminate();
    return 0;
}
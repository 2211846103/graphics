// Includes
#include <shader.hpp>
#include <window.hpp>
#include <graphics_api.hpp>
#include <engine.hpp>
#include <ctime>

using namespace Graphics;

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
    
    Engine::Mesh mesh(&graphics);
    mesh.setVertices(vertices, sizeof(vertices));
    mesh.setIndices(indices, sizeof(indices));

    Engine::Material material(&graphics);
    material.setShader("../res/shaders/shader.vert", "../res/shaders/shader.frag");
    material.setAlbedo("../res/images/test.jpg");

    // Calculating DeltaTime
    int lastTick = clock();
    float dt = 0;

    while (!window.shouldClose()) {
        dt = 1.0 / (clock() - lastTick);

        window.clear(0.2, 0.2, 0.2);

        material.render();
        mesh.render();

        // Checks and call events and swap the buffers
        window.update();
    }

    // Cleans/Deletes all GLFW resources that we allocated.
    glfwTerminate();
    return 0;
}
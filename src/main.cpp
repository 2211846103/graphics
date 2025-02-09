// Includes
#include <shader.hpp>
#include <window.hpp>
#include <graphics_api.hpp>
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

    Shader* shader = graphics.createShader("../res/shaders/shader.vert", "../res/shaders/shader.frag");
    VertexArray* object = graphics.createVertexArray(vertices, sizeof(vertices));
    object->bindIndices(indices, sizeof(indices));

    Texture2D* tex1 = graphics.createTexture2D();
    tex1->config->swizzle_r = BLUE;
    tex1->config->swizzle_g = RED;
    tex1->config->swizzle_b = GREEN;
    tex1->load("../res/images/test2.jpg");

    // Calculating DeltaTime
    int lastTick = clock();
    float dt = 0;

    while (!window.shouldClose()) {
        dt = 1.0 / (clock() - lastTick);

        window.clear(0.2, 0.2, 0.2);

        shader->use();
        tex1->activate(shader, "tex1", 0);
        object->draw();

        // Checks and call events and swap the buffers
        window.update();
    }

    // Cleans/Deletes all GLFW resources that we allocated.
    glfwTerminate();
    return 0;
}
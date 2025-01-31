// Includes
#include <shader.hpp>
#include <window.hpp>
#include <graphics_api.hpp>

using namespace Graphics;

// Main code
int main(int argc, char* argv[]) {
    Window window(800, 600, "test");
    OpenGLGraphicsAPI graphics(window);

    float vertices[] = {
        // Position          // Texture Coords
        -0.5, -0.5, 0.0,     0.0, 0.0,  // Bottom-Left
         0.5, -0.5, 0.0,     1.0, 0.0,  // Bottom-Right
         0.5,  0.5, 0.0,     1.0, 1.0,  // Top-Right

        -0.5, -0.5, 0.0,     0.0, 0.0,  // Bottom-Left
         0.5,  0.5, 0.0,     1.0, 1.0,  // Top-Right
        -0.5,  0.5, 0.0,     0.0, 1.0   // Top-Left
    };

    Shader* shader = graphics.createShader("../res/shaders/shader.vert", "../res/shaders/shader.frag");
    VertexArray* square = graphics.createVertexArray(vertices, sizeof(vertices));

    Texture2D* tex1 = graphics.createTexture2D();
    tex1->config->swizzle_r = BLUE;
    tex1->config->swizzle_g = RED;
    tex1->config->swizzle_b = GREEN;
    tex1->load("../res/images/test2.jpg");

    while (!window.shouldClose()) {
        window.clear(0.2, 0.2, 0.2);

        shader->useShader();

        tex1->activate(shader, "tex1", 0);

        square->draw();

        // Checks and call events and swap the buffers
        window.update();
    }

    // Cleans/Deletes all GLFW resources that we allocated.
    glfwTerminate();
    return 0;
}
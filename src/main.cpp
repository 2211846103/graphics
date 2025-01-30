// Includes
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>
#include <shader.hpp>

#include <window.hpp>
#include <graphics_api.hpp>

using namespace Graphics;

// Main code
int main(int argc, char* argv[]) {
    Window window(800, 600, "test");
    OpenGLGraphicsAPI graphics(window);

    float vertices[] = {
        0.0, 0.5, 0.0,
        0.5, -0.5, 0.0,
        -0.5, -0.5, 0.0
    };

    Shader* shader = graphics.createShader("../res/shaders/shader.vert", "../res/shaders/shader.frag");
    VertexArray* triangle = graphics.createVertexArray(vertices, sizeof(vertices));
    Texture2D* image = graphics.createTexture2D("../res/images/test.jpg");

    while (!window.shouldClose()) {
        window.clear(0.5, 0.5, 0.5);

        shader->setUniform("uniColor");
        triangle->draw();

        // Checks and call events and swap the buffers
        window.update();

    }

    // Cleans/Deletes all GLFW resources that we allocated.
    glfwTerminate();
    return 0;
}
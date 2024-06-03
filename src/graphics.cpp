// Includes
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <window.hpp>
#include <graphics_api.hpp>

using namespace Graphics;

// Main code
int main(int argc, char* argv[]) {
    OpenGLGraphics graphics;
    Window window(800, 600, "test");
    graphics.init(window);

    float vertices[] = {
        0.0, 0.5, 0.0,
        0.5, -0.5, 0.0,
        -0.5, -0.5, 0.0
    };

    OpenGLShader basicShader("../res/shaders/shader.vert", "../res/shaders/shader.frag");

    std::unique_ptr<VertexArray> triangle = graphics.createVertexArray(vertices, 3);

    while (!window.shouldClose())
    {
        window.clear(1.0, 1.0, 1.0);

        basicShader.useShader();
        triangle->draw();

        // Checks and call events and swap the buffers
        window.update();

    }

    // Cleans/Deletes all GLFW resources that we allocated.
    glfwTerminate();
    return 0;
}
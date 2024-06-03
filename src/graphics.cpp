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

    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    graphics.createBuffer(VertexBuffer, vertices, StaticDraw);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
    glEnableVertexAttribArray(0);

    while (!window.shouldClose())
    {
        window.clear(0.5, 0.5, 0.5);

        basicShader.useShader();
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Checks and call events and swap the buffers
        window.update();

    }

    // Cleans/Deletes all GLFW resources that we allocated.
    glfwTerminate();
    return 0;
}
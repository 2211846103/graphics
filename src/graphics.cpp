// Includes
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

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

    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    Buffer* vertexBuffer = graphics.createBuffer(VertexBuffer, vertices, StaticDraw);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
    glEnableVertexAttribArray(0);

    while (!window.shouldClose()) {
        window.clear(0.5, 0.5, 0.5);

        shader->useShader();
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Checks and call events and swap the buffers
        window.update();

    }

    delete vertexBuffer;

    // Cleans/Deletes all GLFW resources that we allocated.
    glfwTerminate();
    return 0;
}
// Includes
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "window.hpp"

using namespace Graphics;

// Main code
int main(int argc, char* argv[]) {

    Window window(800, 600, "test");
    

    while (!window.shouldClose())
    {
        // Checks and call events and swap the buffers
        

        window.update();

    }

    // Cleans/Deletes all GLFW resources that we allocated.
    glfwTerminate();
    return 0;
}
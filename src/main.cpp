// Includes
#include <gameloop.hpp>

using namespace Graphics;
using namespace Engine;
using namespace Math;

// Main code
int main(int argc, char* argv[]) {
    // Preperations
    Window window(800, 600, "test");
    Input::init(&window, CursorDisabled);
    OpenGLGraphicsAPI graphics(window);
    graphics.enableZBuffer();
    graphics.setClearColor({0.2, 0.2, 0.2});
    SceneManager::setGraphicsAPI(&graphics);

    // Calculating DeltaTime
    float dt = 0;  
    
    Start();
    
    Scene* current = SceneManager::getCurrentScene();
    if (current) current->initGameObjects();

    while (!window.shouldClose()) {
        graphics.clear();

        Update(dt);

        if (current) current->updateGameObjects(dt);
        if (current) current->renderGameObjects();

        dt = window.update();
    }

    // Cleans/Deletes all GLFW resources that we allocated.
    glfwTerminate();
    return 0;
}
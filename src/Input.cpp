#include <Input.hpp>

using namespace Engine;
using namespace Graphics;

bool Input::isKeyPressed(Window* window, int key) { return glfwGetKey(window->getWindow(), key) == GLFW_PRESS; }

bool Input::isMouseButtonPressed(Window* window, int button) { return glfwGetMouseButton(window->getWindow(), button) == GLFW_PRESS; }

void Input::getMousePosition(Window* window, double* x, double* y) { glfwGetCursorPos(window->getWindow(), x, y); }

void Input::processInput(Window* window, GameObject* obj) {
    Transform* transform = obj->getComponent<Transform>();

    if (isKeyPressed(window, GLFW_KEY_ESCAPE)) { window->shouldClose(); }
    if (isKeyPressed(window, GLFW_KEY_W)) { transform->position.data.z -= 0.2f; }
    if (isKeyPressed(window, GLFW_KEY_S)) { transform->position.data.z += 0.2f; }
    if (isKeyPressed(window, GLFW_KEY_A)) { transform->position.data.x -= 0.2f; }
    if (isKeyPressed(window, GLFW_KEY_D)) { transform->position.data.x += 0.2f; }
    if (isKeyPressed(window, GLFW_KEY_E)) { transform->position.data.y += 0.2f; }
    if (isKeyPressed(window, GLFW_KEY_Q)) { transform->position.data.y -= 0.2f; }
}


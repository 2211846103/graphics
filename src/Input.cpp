#include <Input.hpp>

using namespace Engine;

Window* Input::window = nullptr;
std::unordered_map<Key, int> Input::_keyToGLFW = {
    {Key::Escape, GLFW_KEY_ESCAPE},
    {Key::W, GLFW_KEY_W},
    {Key::S, GLFW_KEY_S},
    {Key::A, GLFW_KEY_A},
    {Key::D, GLFW_KEY_D},
    {Key::E, GLFW_KEY_E},
    {Key::Q, GLFW_KEY_Q}
};

void Input::init(Window* window) {
    Input::window = window; 
}

bool Input::isKeyPressed(Key key) {
    return glfwGetKey(Input::window->getWindow(), Input::_keyToGLFW[key]) == GLFW_PRESS;
}

bool Input::isMouseButtonPressed(Window* window, int button) { return glfwGetMouseButton(window->getWindow(), button) == GLFW_PRESS; }

void Input::getMousePosition(Window* window, double* x, double* y) { glfwGetCursorPos(window->getWindow(), x, y); }
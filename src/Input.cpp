#include <Input.hpp>

using namespace Engine;

static Vec2 _mousePosition;

Window* Input::window = nullptr;
std::unordered_map<Key, int> Input::_keyToGLFW = {
    {Key::Escape, GLFW_KEY_ESCAPE},
    {Key::W, GLFW_KEY_W},
    {Key::S, GLFW_KEY_S},
    {Key::A, GLFW_KEY_A},
    {Key::D, GLFW_KEY_D},
    {Key::E, GLFW_KEY_E},
    {Key::Q, GLFW_KEY_Q},
    {Key::LSHIFT, GLFW_KEY_LEFT_SHIFT},
    {Key::SPACE, GLFW_KEY_SPACE}
};

static void _mousePosCallback(GLFWwindow* window, double x, double y) {
    _mousePosition = Vec2(x, y);
}

void Input::init(Window* window) {
    Input::window = window;
    glfwSetCursorPosCallback(Input::window->getWindow(), _mousePosCallback);
}

bool Input::isKeyPressed(Key key) {
    return glfwGetKey(Input::window->getWindow(), Input::_keyToGLFW[key]) == GLFW_PRESS;
}

Vec2 Input::getMousePosition() {
    return _mousePosition;
}
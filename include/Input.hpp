#pragma once

#include <window.hpp>
#include <component.hpp>

using namespace Engine;
using namespace Graphics;

class Input {
    public:
        static bool isKeyPressed(Window* window, int key);
        static bool isMouseButtonPressed(Window* window, int button);
        static void getMousePosition(Window* window, double* x, double* y);

        static void processInput(Window* window, GameObject* obj);

};
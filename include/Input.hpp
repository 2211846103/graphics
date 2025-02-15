#pragma once

#include <window.hpp>
#include <component.hpp>

namespace Engine {
    enum Key {
        Escape, W, S, A, D, E, Q
    };

    class Input {
        private:
            static Window* window;
            static std::unordered_map<Key, int> _keyToGLFW;
            
        public:
            static void init(Window* window);

            static bool isKeyPressed(Key key);
            static bool isMouseButtonPressed(Window* window, int button);
            static void getMousePosition(Window* window, double* x, double* y);
    };
}
#pragma once

#include <window.hpp>
#include <component.hpp>

namespace Engine {
    enum Key {
        Escape, W, S, A, D, E, Q, LSHIFT, SPACE
    };

    class Input {
        private:
            static Window* window;
            static std::unordered_map<Key, int> _keyToGLFW;
            
        public:
            static void init(Window* window);
            static bool isKeyPressed(Key key);
            static Vec2 getMousePosition();
    };
}
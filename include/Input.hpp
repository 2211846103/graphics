#pragma once

#include <window.hpp>
#include <component.hpp>

namespace Engine {
    enum Key {
        Escape, W, S, A, D, E, Q, LSHIFT, SPACE
    };

    enum CursorMode {
        CursorNormal, CursorHidden, CursorDisabled, CursorCaptured
    };

    class Input {
        private:
            static Window* window;
            static std::unordered_map<Key, int> _keyToGLFW;
            static std::unordered_map<CursorMode, int> _cursorModeToGLFW;
            
        public:
            static void init(Window* window, CursorMode mode);
            static bool isKeyPressed(Key key);
            static Vec2 getMousePosition();
    };
}
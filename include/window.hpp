#pragma once

#include <glfw/glfw3.h>

namespace Graphics {
    class Window {
        public:
            Window(int w, int h, char* name);
            ~Window();

            bool shouldClose();

            void update();

        private:
            void initWindow();

            int _width;
            int _height;

            char* _windowName;
            GLFWwindow* _window;
    };

}
    
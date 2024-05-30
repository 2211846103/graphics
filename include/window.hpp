#pragma once

#include <glfw/glfw3.h>

namespace GRAPHICS {
    class WINDOW {
        public:
            WINDOW(int w, int h, char* name);
            ~WINDOW();

            bool shouldClose();

        private:
            void initWindow();

            int _width;
            int _height;

            char* _windowName;
            GLFWwindow* window;
    };

}
    
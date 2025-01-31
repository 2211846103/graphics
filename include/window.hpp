#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Graphics {
    class Window {
        private:
            GLFWwindow* _window;

        public:
            int width;
            int height;
            const char* windowName;

            Window(int w, int h, const char* name);
            ~Window();

            bool shouldClose();
            void update();
            void initWindow();
            void clear(float red, float green, float blue);
    };

}
    
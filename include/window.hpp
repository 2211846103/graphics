#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Graphics {
    class Window {
        private:
        float _lastFrame;
        
        public:
            GLFWwindow* _window;
            int width;
            int height;
            const char* windowName;

            Window(int w, int h, const char* name);
            ~Window();

            bool shouldClose();
            float update();
            void initWindow();
            GLFWwindow* getWindow();

            void setSizeCallback(void (*callback)(GLFWwindow* window, int width, int height));
            //void processInput(GameObject* obj, float dt);
    };

}
    
#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Window {

    class IWindow {
        public:
            virtual ~IWindow() = default;

            virtual void initWindow() = 0;
            virtual bool shouldClose() = 0;
            virtual float update() = 0;
    };

    class OpenGLWindow : public IWindow {
        public:
            OpenGLWindow(int width, int height, const char* name);
            ~OpenGLWindow() override;

            void initWindow() override;
            bool shouldClose() override;
            float update() override;

        private:
            GLFWwindow* _window;
            int _width, _height;
            const char* _windowName;
            float _lastFrame;
    };

    class VulkanWindow : public IWindow {
        public:
            VulkanWindow(int width, int height, const char* name);
            ~VulkanWindow() override;

            void initWindow() override;
            bool shouldClose() override;
            float update() override;

        private:
            GLFWwindow* _window;
            int _width, _height;
            const char* _windowName;
    };
}
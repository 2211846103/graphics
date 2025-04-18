#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>



#ifdef __OBJC__
    #import <Cocoa/Cocoa.h>
    #import <QuartzCore/CAMetalLayer.h>
#else
    class NSWindow;
    class NSView;
    class CAMetalLayer;
#endif

namespace engine::rendering {

    class Window {
        public:
            virtual ~Window() = default;

            virtual void initWindow() = 0;
            virtual bool shouldClose() = 0;
            virtual float update() = 0;
    };

#ifdef ENGINE_COMPILE_OPENGL
    class OpenGLWindow : public Window {
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
#endif

#ifdef ENGINE_COMPILE_VULKAN
    class VulkanWindow : public Window {
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
#endif

#ifdef ENGINE_COMPILE_METAL
    class MetalWindow : public Window {
        public:
            MetalWindow(int width, int height, const char* name);
            ~MetalWindow() override;

            void initWindow() override;
            bool shouldClose() override;
            float update() override;

        private:
            int _width;                  
            int _height;                 
            const char* _windowName;    

            NSWindow* _window;
            NSView* _contentView;
            CAMetalLayer* _metalLayer;
    };
#endif

#ifdef ENGINE_COMPILE_DIRECTX
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

extern ID3D11Device* device;
extern ID3D11DeviceContext* context;
extern IDXGISwapChain* swapChain;
    class DirectXWindow : public Window {
        public:
            DirectXWindow(int width, int height, const char* name);
            ~DirectXWindow() override;

            void initWindow() override;
            bool shoudlClose() override;
            float update() override;

        private:
            int _width;
            int _height;
            const char* _windowName;
            
    };
#endif
}

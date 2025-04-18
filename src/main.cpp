#include <renderer/window.hpp>
#include <iostream>

using namespace engine::rendering;

int main() {
#ifdef ENGINE_COMPILE_DIRECTX
    std::cout << "Initializing Vulkan window..." << std::endl;

    DirectXWindow window(800, 600, "Vulkan Window");
    window.initWindow();

    float dt = 0;

    while (!window.shouldClose()) {
        std::cout << "Running update loop..." << std::endl;
        dt = window.update();
    }

    std::cout << "Window closed successfully." << std::endl;
#endif

    return 0;
}

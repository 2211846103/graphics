#include <renderer/window.hpp>


using namespace engine;

int main() {
#ifdef ENGINE_COMPILE_DIRECTX
  VulkanWindow window(800, 600, "OpenGL Window");
  window.initWindow();

  float dt = 0;

  while (!window.shouldClose()) {
    dt = window.update();
  }

  glfwTerminate();
  std::cout << "Window closed successfully." << std::endl;
#endif

  return 0;
}

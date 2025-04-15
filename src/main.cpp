#include <renderer/window.hpp>
#include <resources/resource_manager.hpp>

using namespace engine::rendering;
using namespace engine::resources;

int main() {
  OpenGLWindow window(800, 600, "OpenGL Window");
  window.initWindow();

  float dt = 0;

  while (!window.shouldClose()) {
    dt = window.update();
  }

  glfwTerminate();
  std::cout << "Window closed successfully." << std::endl;

  return 0;
}

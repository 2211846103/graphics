#include <renderer/window.hpp>

#include <iostream>

using namespace engine::rendering;

int main() {
  OpenGLWindow window(800, 600, "OpenGL Window");
  window.initWindow();
  
  while (!window.shouldClose()) {
    window.update();
  }

  glfwTerminate();
  std::cout << "Window closed successfully." << std::endl;

  return 0;
}

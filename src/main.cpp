#include <window.hpp>

#include <iostream>

using namespace Window;

int main() {
  Window::OpenGLWindow window(800, 600, "OpenGL Window");
  window.initWindow();
  
  while (!window.shouldClose()) {
    window.update();
  }

  glfwTerminate();
  std::cout << "Window closed successfully." << std::endl;

  return 0;
}

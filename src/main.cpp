#include <core/types.hpp>
#include <renderer/window.hpp>
#include <resource_management/resource_manager.hpp>
#include <unistd.h>

using namespace engine::rendering;

int main() {

  /* Resource Management Shit */
  using namespace engine::resource_management;
  using namespace engine::core;

  FactoryManager::setGraphicsAPI(GraphicsAPI::OpenGL);
  ResourceManager manager(true);

  //std::cout << "\nTesting\n" << std::endl;
  //Shader* shader = manager.loadShader("/home/Zenjar/Documents/projects/graphics_assets/shader.vert", "/home/Zenjar/Documents/projects/graphics_assets/shader.frag").get();
  //std::cout << "\nEnd Testing\n" << std::endl;


#ifdef ENGINE_COMPILE_OPENGL
    std::cout << "Initializing Metal window..." << std::endl;

    OpenGLWindow window(800, 600, "Metal Window");
    window.initWindow();

    float dt = 0;

    while (!window.shouldClose()) {
        dt = window.update();
    }

    std::cout << "Window closed successfully." << std::endl;
#endif

  return 0;
}

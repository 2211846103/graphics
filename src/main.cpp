#include <iostream>
#include <core/types.hpp>
#include <memory>
#include <renderer/window.hpp>
#include <resource_management/resource_manager.hpp>
#include <unistd.h>

using namespace engine::rendering;

int main() {
#ifdef ENGINE_COMPILE_VULKAN
    std::cout << "Initializing Metal window..." << std::endl;

    OpenGLWindow window(800, 600, "Metal Window");
    window.initWindow();

    float dt = 0;

    while (!window.shouldClose()) {
        std::cout << "Running update loop..." << std::endl;
        dt = window.update();
    }

    std::cout << "Window closed successfully." << std::endl;
#endif

  using namespace engine::resource_management;
  using namespace engine::core;

  FactoryManager::setGraphicsAPI(GraphicsAPI::OpenGL);
  ResourceManager manager;

  std::shared_ptr<Shader> vertex = manager.shader_manager.load("vert.path", ShaderType::Vertex);
  std::shared_ptr<Shader> fragment = manager.shader_manager.load("frag.path", ShaderType::Fragment);

  std::shared_ptr<ShaderPipeline> pipeline = manager.pipeline_manager.load(vertex, fragment);
  std::cout << "\nTesting\n" << std::endl;
  vertex->reload();
  std::cout << "\nEnd Testing\n" << std::endl;

  return 0;
}

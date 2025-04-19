#include "resource_management/shader.hpp"
#include <memory>
#include <resource_management/factory.hpp>


using namespace engine::resource_management;

std::unique_ptr<GraphicsFactory> FactoryManager::graphics_factory = std::make_unique<OpenGLGraphicsFactory>();

void FactoryManager::setGraphicsAPI(core::GraphicsAPI api) {
  switch (api) {
#ifdef ENGINE_COMPILE_OPENGL
    case core::GraphicsAPI::OpenGL:
      graphics_factory = std::make_unique<OpenGLGraphicsFactory>();
      break;
#endif
#ifdef ENGINE_COMPILE_VULKAN
    case core::GraphicsAPI::Vulkan:
      //graphics_factory = std::make_unique<VulkanGraphicsFactory>();
      break;
#endif
#ifdef ENGINE_COMPILE_DIRECTX
    case core::GraphicsAPI::DirectX:
      //graphics_factory = std::make_unique<DirectXGraphicsFactory>();
      break;
#endif
#ifdef ENGINE_COMPILE_METAL
    case core::GraphicsAPI::Metal:
      //graphics_factory = std::make_unique<MetalGraphicsFactory>();
      break;
#endif
  }
}

#ifdef ENGINE_COMPILE_OPENGL
std::shared_ptr<Shader> OpenGLGraphicsFactory::createShader(std::shared_ptr<File> vertex, std::shared_ptr<File> fragment, std::string name, bool lazy) {
  return std::make_shared<OpenGLShader>(vertex, fragment, name, lazy);
}
#endif

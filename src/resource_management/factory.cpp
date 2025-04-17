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
std::shared_ptr<Shader> OpenGLGraphicsFactory::createShader(std::string path, ShaderType type, std::string name) {
  return std::make_shared<OpenGLShader>(path, type, name);
}
std::shared_ptr<ShaderPipeline> OpenGLGraphicsFactory::createShaderPipeline(std::shared_ptr<Shader> vertex, std::shared_ptr<Shader> fragment, std::string name) {
  return std::make_shared<OpenGLShaderPipeline>(vertex, fragment, name);
}
#endif

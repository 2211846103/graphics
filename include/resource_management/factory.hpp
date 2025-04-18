#pragma once

#include <memory>
#include <core/types.hpp>
#include <resource_management/shader.hpp>
#include <string>


namespace engine::resource_management {

class GraphicsFactory {
public:
  virtual std::shared_ptr<Shader> createShader(std::shared_ptr<File> vertex, std::shared_ptr<File> fragment, std::string name = "") = 0;
};

#ifdef ENGINE_COMPILE_OPENGL
class OpenGLGraphicsFactory : public GraphicsFactory {
public:
  std::shared_ptr<Shader> createShader(std::shared_ptr<File> vertex, std::shared_ptr<File> fragment, std::string name = "") override;
};
#endif

class FactoryManager {
public:
  static std::unique_ptr<GraphicsFactory> graphics_factory;
  static void setGraphicsAPI(core::GraphicsAPI api);
};

}

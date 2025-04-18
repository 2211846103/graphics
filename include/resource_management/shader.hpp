#pragma once

#include <memory>
#include <resource_management/resource.hpp>
#include <resource_management/file.hpp>


namespace engine::resource_management {

class Shader : public Resource {
public:
  std::shared_ptr<File> vertex_shader;
  std::shared_ptr<File> fragment_shader;

  Shader(std::shared_ptr<File> vertex, std::shared_ptr<File> fragment, std::string name = "");
  ~Shader() = default;

  void linkDependencies() override;
};

#ifdef ENGINE_COMPILE_OPENGL
class OpenGLShader : public Shader {
private:
  void load() override;
  void unload() override;

public:
  OpenGLShader(std::shared_ptr<File> vertex, std::shared_ptr<File> fragment, std::string name = "");
  ~OpenGLShader();
};
#endif

}

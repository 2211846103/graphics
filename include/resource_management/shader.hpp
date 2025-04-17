#pragma once

#include <memory>
#include <resource_management/resource.hpp>


namespace engine::resource_management {

enum class ShaderType {
  Vertex, Fragment
};

class Shader : public Resource {
public:
  std::string path;
  ShaderType shader_type;

  Shader(std::string path, ShaderType type, std::string name = "");
  ~Shader() = default;
};

class ShaderPipeline : public Resource {
public:
  std::shared_ptr<Shader> vertex_shader;
  std::shared_ptr<Shader> fragment_shader;

  ShaderPipeline(std::string name = "");
  ~ShaderPipeline() = default;

  void setShader(std::shared_ptr<Shader> shader);
};

#ifdef ENGINE_COMPILE_OPENGL
class OpenGLShader : public Shader {
private:
  void load() override;
  void unload() override;

public:
  OpenGLShader(std::string path, ShaderType type, std::string name = "");
  ~OpenGLShader();
};

class OpenGLShaderPipeline : public ShaderPipeline {
private:
  void load() override;
  void unload() override;

public:
  OpenGLShaderPipeline(std::string name = "");
  ~OpenGLShaderPipeline();
};
#endif

}

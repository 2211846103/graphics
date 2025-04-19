#pragma once

#include <memory>
#include <resource_management/resource.hpp>
#include <resource_management/file.hpp>

namespace engine::resource_management {

class Shader : public Resource {
public:
  std::shared_ptr<File> vertex_shader;
  std::shared_ptr<File> fragment_shader;

  Shader(std::shared_ptr<File> vertex, std::shared_ptr<File> fragment, std::string name = "", bool lazy = true);
  ~Shader() = default;

  void linkDependencies() override;

  virtual void useShader() {};
};

#ifdef ENGINE_COMPILE_OPENGL
class OpenGLShader : public Shader {
private:
  unsigned int vertex_shader_id;
  unsigned int fragment_shader_id;
  unsigned int shader_program;

  void load() override;
  void unload() override;

public:
  OpenGLShader(std::shared_ptr<File> vertex, std::shared_ptr<File> fragment, std::string name = "", bool lazy = true);
  ~OpenGLShader();

  void useShader() override;
};
#endif

#ifdef ENGINE_COMPILE_METAL
#import <Metal/Metal.h>

class MetalShader : public Shader {
private:
  void load() override;
  void unload() override;

public:
  id<MTLLibrary> library;
  id<MTLFunction> vertex_function;
  id<MTLFunction> fragment_function;
  id<MTLRenderPipelineState> pipeline_state;

  MetalShader(std::shared_ptr<File> vertex, std::shared_ptr<File> fragment, std::string name = "", bool lazy = true);
  ~MetalShader();

  void useShader() override;
};
#endif

}

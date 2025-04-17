#include <iostream>
#include <memory>
#include <resource_management/shader.hpp>
#include <string>


using namespace engine::resource_management;

Shader::Shader(std::string path, ShaderType type, std::string name) :
Resource(ResourceType::Shader, name) {
  this->path = path;
  this->shader_type = type;
}

ShaderPipeline::ShaderPipeline(std::string name) :
Resource(ResourceType::ShaderPipeline, name) {}
void ShaderPipeline::setShader(std::shared_ptr<Shader> shader) {
  switch (shader->shader_type) {
    case ShaderType::Vertex:
      vertex_shader = shader;
      break;
    case ShaderType::Fragment:
      fragment_shader = shader;
      break;
  }

  this->reload();
}

#ifdef ENGINE_COMPILE_OPENGL
OpenGLShader::OpenGLShader(std::string path, ShaderType type, std::string name) :
Shader(path, type, name) {
  this->load();
}
OpenGLShader::~OpenGLShader() {
  this->unload();
}
void OpenGLShader::load() {
  std::cout << "Loading OpenGLShader" << std::endl;
}
void OpenGLShader::unload() {
  std::cout << "Unloading OpenGLShader" << std::endl;
}

OpenGLShaderPipeline::OpenGLShaderPipeline(std::string name) :
ShaderPipeline(name) {
  this->load();
}
OpenGLShaderPipeline::~OpenGLShaderPipeline() {
  this->unload();
}
void OpenGLShaderPipeline::load() {
  std::cout << "Loading OpenGLShaderPipeline" << std::endl;
}
void OpenGLShaderPipeline::unload() {
  std::cout << "Unloading OpenGLShaderPipeline" << std::endl;
}
#endif

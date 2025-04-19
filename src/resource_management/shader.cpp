#include <iostream>
#include <memory>
#include <resource_management/shader.hpp>
#include <string>


using namespace engine::resource_management;

Shader::Shader(std::shared_ptr<File> vertex, std::shared_ptr<File> fragment, std::string name, bool lazy) :
Resource(ResourceType::Shader, name, lazy) {
  this->vertex_shader = vertex;
  this->fragment_shader = fragment;
}

void Shader::linkDependencies() {
  vertex_shader->dependents.push_back(weak_from_this());
  fragment_shader->dependents.push_back(weak_from_this());
}

#ifdef ENGINE_COMPILE_OPENGL
OpenGLShader::OpenGLShader(std::shared_ptr<File> vertex, std::shared_ptr<File> fragment, std::string name, bool lazy) :
Shader(vertex, fragment, name, lazy) {
  if (!lazy) this->load();
}

OpenGLShader::~OpenGLShader() {
  this->unload();
}

void OpenGLShader::load() {
  if (this->loaded) return;

  std::cout << "Loading OpenGLShader" << std::endl;

  this->loaded = true;
}
void OpenGLShader::unload() {
  if (!this->loaded) return;

  std::cout << "Unloading OpenGLShader" << std::endl;

  this->loaded = false;
}
#endif

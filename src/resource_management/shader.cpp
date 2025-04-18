#include <iostream>
#include <memory>
#include <resource_management/shader.hpp>
#include <string>


using namespace engine::resource_management;

Shader::Shader(std::shared_ptr<File> vertex, std::shared_ptr<File> fragment, std::string name) :
Resource(ResourceType::Shader, name) {
  this->vertex_shader = vertex;
  this->fragment_shader = fragment;
}

void Shader::linkDependencies() {
  vertex_shader->dependents.push_back(weak_from_this());
  fragment_shader->dependents.push_back(weak_from_this());
}

#ifdef ENGINE_COMPILE_OPENGL
OpenGLShader::OpenGLShader(std::shared_ptr<File> vertex, std::shared_ptr<File> fragment, std::string name) :
Shader(vertex, fragment, name) {
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
#endif

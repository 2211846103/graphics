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

  unsigned int vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
  unsigned int fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

  glShaderSourse(vertex_shader_id, 1, &vertex_shader->read(), NULL);
  glShaderSourse(fragment_shader_id, 1, &fragment_shader->read(), NULL);

  glCompileShader(vertex_shader_id);
  glCompileShader(fragment_shader_id);

  int success;
  char infoLog[512];

  glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertex_shader_id, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
  }

  glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragment_shader_id, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
  }

  unsigned int shader_program = glCreateProgram();
  glAttachShader(shader_program, vertex_shader_id);
  glAttachShader(shader_program, fragment_shader_id);
  glLinkProgram(shader_program);

  glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shader_program, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
  }

  this->loaded = true;
}

void OpenGLShader::unload() {
  if (!this->loaded) return;

  glDeleteShader(vertex_shader_id);
  glDeleteShader(fragment_shader_id);
  glDeleteProgram(shader_program);

  std::cout << "Unloading OpenGLShader" << std::endl;

  this->loaded = false;
}

void OpenGLShader::useShader() {
  glUseProgram(shader_program);
}
#endif

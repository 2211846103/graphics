#include <iostream>
#include <memory>
#include <resources/shader.hpp>
#include <string>


using namespace engine::resources;

// Shader
Shader::Shader(const std::string& name, const std::string& path) :
Resource(name, path, ResourceType::Shader) {
  this->load();
}
Shader::~Shader() {
  this->unload();
}
void Shader::load() {
  std::cout << "Loading" << std::endl;
}
void Shader::unload() {
  std::cout << "Unloading" << std::endl;
}

// ShaderStorage
std::shared_ptr<Shader> ShaderStorage::get(const std::string& name) {
  auto itr = _storage.find(name);
  if (itr == _storage.end()) return nullptr;
  return itr->second;
}
std::shared_ptr<Shader> ShaderStorage::load(const std::string& name, const std::string& path) {
  std::shared_ptr<Shader> shader = this->get(name);
  if (shader) {
    if (path == shader->path) return shader;
    
    shader->path = path;
    shader->reload();
    return shader;
  }

  shader = std::make_shared<Shader>(name, path);
  _storage[name] = shader;
  return shader;
}

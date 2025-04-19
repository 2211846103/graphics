#include "resource_management/factory.hpp"
#include "resource_management/shader.hpp"
#include <memory>
#include <resource_management/resource_storage.hpp>


using namespace engine::resource_management;

std::map<std::string, std::shared_ptr<File>> FileStorage::_storage = {};
std::map<std::string, std::shared_ptr<Shader>> ShaderStorage::_storage = {};

std::shared_ptr<File> FileStorage::get(std::string name) {
  auto file = _storage.find(name);
  if (file != _storage.end()) return file->second;
  return nullptr;
}

std::shared_ptr<File> FileStorage::load(std::string path, std::string name, bool hot_reload, bool lazy) {
  std::shared_ptr<File> file = this->get(name);
  if (file) return file;

  file = std::make_shared<File>(path, name, hot_reload, lazy);
  _storage[file->name] = file;
  return file;
}

std::shared_ptr<Shader> ShaderStorage::get(std::string name) {
  auto shader = _storage.find(name);
  if (shader != _storage.end()) return shader->second;
  return nullptr;
}

std::shared_ptr<Shader> ShaderStorage::load(std::shared_ptr<File> vertex, std::shared_ptr<File> fragment, std::string name, bool lazy) {
  std::shared_ptr<Shader> shader = this->get(name);
  if (shader) return shader;

  shader = FactoryManager::graphics_factory->createShader(vertex, fragment, name, lazy);
  shader->linkDependencies();
  _storage[shader->name] = shader;
  return shader;
}

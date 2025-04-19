#include "resource_management/file.hpp"
#include <memory>
#include <resource_management/resource_manager.hpp>


using namespace engine::resource_management;

ResourceManager::ResourceManager(bool hot_reload) : _hot_reload(hot_reload) {}

std::shared_ptr<File> ResourceManager::getFile(std::string name) {
  return _file_storage.get(name);
}
std::shared_ptr<Shader> ResourceManager::getShader(std::string name) {
  return _shader_storage.get(name);
}

std::shared_ptr<File> ResourceManager::loadFile(std::string path, std::string name, bool lazy) {
  return _file_storage.load(path, name, this->_hot_reload, lazy);
}
std::shared_ptr<Shader> ResourceManager::loadShader(std::string vertex_path, std::string fragment_path, std::string name, bool lazy) {
  std::shared_ptr<File> vertex_file = this->loadFile(vertex_path, "", lazy);
  std::shared_ptr<File> fragment_file = this->loadFile(fragment_path, "", lazy);

  return _shader_storage.load(vertex_file, fragment_file, name, lazy);
}

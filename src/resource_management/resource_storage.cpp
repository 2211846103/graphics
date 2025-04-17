#include "resource_management/factory.hpp"
#include "resource_management/shader.hpp"
#include <memory>
#include <resource_management/resource_storage.hpp>


using namespace engine::resource_management;

std::shared_ptr<Shader> ShaderStorage::get(std::string path) {
  auto shader = _storage.find(path);
  if (shader != _storage.end()) return shader->second;
  return nullptr;
}

std::shared_ptr<Shader> ShaderStorage::load(std::string path, ShaderType type, std::string name) {
  std::shared_ptr<Shader> shader = this->get(path);
  if (shader) return shader;

  shader = FactoryManager::graphics_factory->createShader(path, type, name);
  _storage[shader->path] = shader;
  return shader;
}

std::shared_ptr<ShaderPipeline> ShaderPipelineStorage::get(std::string name) {
  auto pipeline = _storage.find(name);
  if (pipeline != _storage.end()) return pipeline->second;
  return nullptr;
}

std::shared_ptr<ShaderPipeline> ShaderPipelineStorage::load(std::string name) {
  std::shared_ptr<ShaderPipeline> pipeline = this->get(name);
  if (pipeline) return pipeline;

  pipeline = FactoryManager::graphics_factory->createShaderPipeline(name);
  _storage[pipeline->name] = pipeline;
  return pipeline;
}

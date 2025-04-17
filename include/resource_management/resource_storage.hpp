#pragma once

#include "resource_management/shader.hpp"
#include <map>
#include <memory>
#include <resource_management/factory.hpp>


namespace engine::resource_management {

class ShaderStorage {
private:
  std::map<std::string, std::shared_ptr<Shader>> _storage;

public:
  std::shared_ptr<Shader> load(std::string path, ShaderType type, std::string name = "");
  std::shared_ptr<Shader> get(std::string name);
};

class ShaderPipelineStorage {
private:
  std::map<std::string, std::shared_ptr<ShaderPipeline>> _storage;

public:
  std::shared_ptr<ShaderPipeline> load(std::shared_ptr<Shader> vertex, std::shared_ptr<Shader> fragment, std::string name = "");
  std::shared_ptr<ShaderPipeline> get(std::string name);
};

}

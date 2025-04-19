#pragma once

#include <memory>
#include <resource_management/resource_storage.hpp>


namespace engine::resource_management {

class ResourceManager {
private:
  bool _hot_reload;
  FileStorage _file_storage;
  ShaderStorage _shader_storage;

public:
  ResourceManager(bool hot_reload = false);
  ~ResourceManager() = default;

  void setGraphicsLoader(core::GraphicsAPI api);

  std::shared_ptr<File> getFile(std::string name);
  std::shared_ptr<Shader> getShader(std::string name);

  std::shared_ptr<File> loadFile(std::string path, std::string name = "", bool lazy = true);
  std::shared_ptr<Shader> loadShader(std::string vertex_path, std::string fragment_path, std::string name = "", bool lazy = true);
};

}

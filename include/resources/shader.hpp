#pragma once

#include <map>
#include <memory>
#include <resources/resource.hpp>


namespace engine::resources {

class Shader : public Resource {
public:
  Shader(const std::string& name, const std::string& path);
  ~Shader();

  void load() override;
  void unload() override;
};

class ShaderStorage {
private:
  std::map<std::string, std::shared_ptr<Shader>> _storage;

public:
  std::shared_ptr<Shader> get(const std::string& name);
  std::shared_ptr<Shader> load(const std::string& name, const std::string& path);
};

}

#pragma once

#include <ostream>
#include <string>


namespace engine::resources {

enum class ResourceType {
  Shader, ShaderPipeline
};

class Resource {
public:
  // Members
  std::string name;
  std::string path;
  ResourceType resource_type;
  bool loaded = false;
  int ref_count = 0;
  size_t size = 0;

  // Constrcutors and Deconstructors
  Resource(const std::string& name, const std::string& path, const ResourceType& type);
  virtual ~Resource() = default;

  // Abstract Methods
  virtual void load() = 0;
  virtual void unload() = 0;

  // Concrete Methods
  friend std::ostream& operator<<(std::ostream& out, const Resource& resource);
  void reload();
};

}

#pragma once

#include <cstdint>
#include <ctime>
#include <string>


namespace engine::resource_management {

enum class ResourceType {
  Shader, ShaderPipeline
};

class Resource {
protected:
  virtual void load() = 0;
  virtual void unload() = 0;

public:
  int resource_id;
  std::string name;
  bool loaded;
  uint32_t version;
  int ref_count;
  ResourceType resource_type;
  bool dirty;
  time_t last_used;
  size_t memory_size;

  Resource(ResourceType type, std::string name = "");
  ~Resource() = default;

  void reload();
};

}

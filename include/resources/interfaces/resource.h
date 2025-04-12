#pragma once

#include <string>


namespace engine::resources {

enum class ResourceType {
  Shader
};

class Resource {
public:
  size_t id;
  std::string path;
  ResourceType type;
};

}

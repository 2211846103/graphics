#pragma once

#include <string>


namespace engine::resources {

enum class ResourceType {};

enum class LoadState {
  Unloaded, Loading, Loaded, Failed
};

class Resource {
  // int or string identifier
  ResourceType type;
  std::string path;
  LoadState load_state;
};

}

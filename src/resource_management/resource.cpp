#include <chrono>
#include <resource_management/resource.hpp>
#include <string>


using namespace engine::resource_management;

Resource::Resource(ResourceType type, std::string name) :
resource_type(type) {
  this->name = name.empty() ? std::to_string(
    std::hash<std::string>{}(
      std::to_string(
        std::chrono::high_resolution_clock::now().time_since_epoch().count()
      )
    )
  ) : name;
}

void Resource::reload() {
  this->unload();
  this->load();
}

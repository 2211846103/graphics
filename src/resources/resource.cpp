#include <ostream>
#include <resources/resource.hpp>
#include <string>


using namespace engine::resources;

Resource::Resource(const std::string& name, const std::string& path, const ResourceType& type) :
name(name), path(path), resource_type(type) {}
void Resource::reload() {
  this->unload();
  this->load();
}

namespace engine::resources {

inline std::ostream& operator<<(std::ostream& out, const Resource& resource) {
  out << "{"
      << "\"name\": \"" << resource.name << "\","
      << "\"loaded\": " << resource.loaded << ","
      << "\"ref_count\": " << resource.ref_count << ","
      << "\"size\": " << resource.size
      << "}";

  return out;
}

}

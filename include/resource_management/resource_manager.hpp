#pragma once

#include <resource_management/resource_storage.hpp>


namespace engine::resource_management {

class ResourceManager {
public:
  ShaderStorage shader_manager;
  ShaderPipelineStorage pipeline_manager;
};

}

#pragma once


namespace engine::core {

enum class GraphicsAPI {
  OpenGL,
#ifdef ENGINE_VULKAN
  Vulkan,
#endif
#ifdef ENGINE_DIRECTX
  DirectX,
#endif
};

class Config {
public:
  static GraphicsAPI graphics_api;
};

}

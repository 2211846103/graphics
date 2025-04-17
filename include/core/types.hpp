#pragma once


namespace engine::core {

enum class GraphicsAPI {
#ifdef ENGINE_COMPILE_OPENGL
  OpenGL,
#endif
#ifdef ENGINE_COMPILE_VULKAN
  Vulkan,
#endif
#ifdef ENGINE_COMPILE_DIRECTX
  DirectX,
#endif
#ifdef ENGINE_COMPILE_METAL
  Metal,
#endif
};

}

file(GLOB SRC "*.cpp")

add_library(renderer ${SRC})

if (ENABLE_METAL)
  file(GLOB OBJ_SRC "*.mm")
  target_sources(renderer ${OBJ_SRC})
  target_link_libraries(renderer ${METAL_LIBS})
elseif(ENABLE_OPENGL OR ENABLE_VULKAN)
  target_link_libraries(renderer ${OPENGL_LIBS})
elseif(ENABLE_DIRECTX)
  target_sources(renderer ${DIRECTX_LIBS})
endif()

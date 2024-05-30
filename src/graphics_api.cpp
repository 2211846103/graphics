#include <graphics_api.hpp>

Graphics::Buffer Graphics::GraphicsApi::createBuffer(void* data) {
    Graphics::Buffer buffer;
    buffer.setData(data);
    return buffer;
}
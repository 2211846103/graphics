#include "graphics_api.hpp"

void init(int x, int y, int width, int height) {
    glViewport(x, y, width, height);
}
#include <graphics_api.hpp>

Graphics::Buffer Graphics::GraphicsApi::createBuffer(void* data) {
    Graphics::Buffer buffer;
    buffer.setData(data);
    return buffer;
}
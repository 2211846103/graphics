#include <graphics_api.hpp>

using namespace Graphics;

void OpenGLGraphics::init(Window &window) {
    glViewport(0, 0, window.width, window.height);
}

Buffer GraphicsApi::createBuffer(void* data) {
    Graphics::Buffer buffer;
    buffer.setData(data);
    return buffer;
}
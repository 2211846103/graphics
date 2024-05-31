#include <graphics_api.hpp>

void Graphics::OpenGLGraphics::init(int x, int y, int width, int height) {
    glViewport(x, y, width, height);
}

Graphics::Buffer Graphics::OpenGLGraphics::createBuffer(BufferType type, void* data, BufferUsage usage) {
    Graphics::OpenGLBuffer buffer;

    switch(usage) {
        case StaticDraw:
            buffer.usage = GL_STATIC_DRAW; break;
        case DynamicDraw:
            buffer.usage = GL_DYNAMIC_DRAW; break;
        case StreamDraw:
            buffer.usage = GL_STREAM_DRAW; break;
        case StaticCopy:
            buffer.usage = GL_STATIC_COPY; break;
        case DynamicCopy:
            buffer.usage = GL_DYNAMIC_COPY; break;
        case StreamCopy:
            buffer.usage = GL_STREAM_COPY; break;
        case StaticRead:
            buffer.usage = GL_STATIC_READ; break;
        case DynamicRead:
            buffer.usage = GL_DYNAMIC_READ; break;
        case StreamRead:
            buffer.usage = GL_STREAM_READ; break;
        default:
            buffer.usage = 0;
    }
    
    glGenBuffers(1, &buffer.id);
    buffer.bind(type);
    buffer.setData(data);

    return buffer;
}
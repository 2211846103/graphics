#pragma once

namespace Graphics {
    enum BufferUsage {
        STATIC_DRAW, DYNAMIC_DRAW, STREAM_DRAW
    };

    class Buffer {
        public:
            void* data;
            BufferUsage usage;

            void bind();
            void unbind();
            void setData(void* data);
    };    
}
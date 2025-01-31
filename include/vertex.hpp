#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <graphics_components.hpp>

namespace Graphics {
    class Vertex {
        public:
            const size_t floatPerVer = 11;

            Vector3D position;
            Vector4D color;
            Vector3D normal;
            Vector2D uv;

            Vertex(Vector3D pos, Vector4D col, Vector3D nor, Vector2D uv);
            
            float* toFloat();
    };
}
#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Graphics {
    struct Vector3D {
        float x;
        float y;
        float z;
    };

    struct Vector2D {
        float x;
        float y;
    };

    class Vertex {
        public:
            const size_t floatPerVer = 11;

            Vector3D position;
            Vector3D color;
            Vector3D normal;
            Vector2D uv;

            Vertex(Vector3D pos, Vector3D col, Vector3D nor, Vector2D uv);
            
            float* toFloat(Vertex* verArr[], int numOfVertices);
    };
}
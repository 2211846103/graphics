#include <vertex.hpp>

using namespace Graphics;

Vertex::Vertex(Vector3D pos, Vector4D col, Vector3D nor, Vector2D uv) {
    this->position = pos;
    this->color = col;
    this->normal = nor;
    this->uv = uv;
}

float* Vertex::toFloat() {
    
}
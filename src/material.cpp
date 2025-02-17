#include <material.hpp>

using namespace Engine;

Material::Material(GraphicsAPI* api) {
    this->_api = api;
    this->ambient = {0.2125, 0.1275, 0.054};
    this->diffuse = {0.714, 0.4284, 0.18144};
    this->specular = {0.393548, 0.271906, 0.166721};
    this->shininess = 0.2;
}

Material::~Material() {
    if (this->albedo) delete this->albedo;
}

void Material::setAlbedo(const char* path) {
    if (this->albedo) delete this->albedo;
    this->albedo = this->_api->createTexture2D(path);
}
#include <material.hpp>

using namespace Engine;

Material::Material(GraphicsAPI* api) {
    this->_api = api;
    this->ambient = {0, 0, 0};
    this->diffuse = {0.55, 0.55, 0.55};
    this->specular = {0.70, 0.70, 0.70};
    this->shininess = 0.25;
}

Material::~Material() {
    if (this->albedo) delete this->albedo;
}

void Material::setAlbedo(const char* path) {
    if (this->albedo) delete this->albedo;
    this->albedo = this->_api->createTexture2D(path);
}
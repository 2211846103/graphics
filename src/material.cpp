#include <material.hpp>

using namespace Engine;

Material::Material(GraphicsAPI* api) {
    this->_api = api;
}

Material::~Material() {
    delete this->albedo;
}

void Material::setAlbedo(const char* path) {
    this->albedo = this->_api->createTexture2D(path);
}
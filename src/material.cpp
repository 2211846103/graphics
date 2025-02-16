#include <material.hpp>

using namespace Engine;

Material::Material(GraphicsAPI* api) {
    this->_api = api;
    this->setColor(Vec4(240, 240, 240, 255));
}

Material::~Material() {
    delete this->albedo;
}

void Material::setColor(Vec4 color) {
    if (this->albedo) delete this->albedo;
    this->albedo = this->_api->createTexture2D(color);
}

void Material::setAlbedo(const char* path) {
    if (this->albedo) delete this->albedo;
    this->albedo = this->_api->createTexture2D(path);
}
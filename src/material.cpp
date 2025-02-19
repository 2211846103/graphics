#include <material.hpp>

using namespace Engine;

Material::Material(GraphicsAPI* api) {
    this->_api = api;
    this->setAlbedo({0.8, 0.8, 0.8, 1});
    this->setSpecular({1, 1, 1, 1});
    this->shininess = 0.1;
}

Material::~Material() {
    if (this->albedo) delete this->albedo;
}

void Material::setAlbedo(Vec4 color) {
    if (this->albedo) delete this->albedo;
    this->albedo = this->_api->createTexture2D(color);
}

void Material::setAlbedo(const char* path) {
    if (this->albedo) delete this->albedo;
    this->albedo = this->_api->createTexture2D(path);
}

void Material::setSpecular(Vec4 color) {
    if (this->specular) delete this->specular;
    this->specular = this->_api->createTexture2D(color);
}

void Material::setSpecular(const char* path) {
    if (this->specular) delete this->specular;
    this->specular = this->_api->createTexture2D(path);
}
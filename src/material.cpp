#include <material.hpp>

using namespace Engine;

Material::Material(GraphicsAPI* api) {
    this->_api = api;
    this->setAlbedo({0.714, 0.4284, 0.18144});
    this->setSpecular({0.393548, 0.271906, 0.166721});
    this->shininess = 0.2;
}

Material::~Material() {
    if (this->albedo) delete this->albedo;
}

void Material::setAlbedo(Vec3 color) {
    if (this->albedo) delete this->albedo;
    this->albedo = this->_api->createTexture2D(Vec4(color.x(), color.y(), color.z(), 1.0));
}

void Material::setAlbedo(const char* path) {
    if (this->albedo) delete this->albedo;
    this->albedo = this->_api->createTexture2D(path);
}

void Material::setSpecular(Vec3 color) {
    if (this->specular) delete this->specular;
    this->specular = this->_api->createTexture2D(Vec4(color.x(), color.y(), color.z(), 1.0));
}

void Material::setSpecular(const char* path) {
    if (this->specular) delete this->specular;
    this->specular = this->_api->createTexture2D(path);
}
#include <component.hpp>

using namespace Engine;
using namespace Graphics;

Material::Material(GraphicsAPI* api) {
    this->_api = api;
}
Material::~Material() {
    delete this->albedo;
}
void Material::setAlbedo(const char* path) {
    this->albedo = this->_api->createTexture2D(path);
}
void Material::init() {}
void Material::update(float dt) {}
void Material::render() {}

Mesh::Mesh(GraphicsAPI* api) {
    this->_api = api;
}
Mesh::~Mesh() {
    delete this->_vao;
}
void Mesh::setVertices(Vertex* vertices, size_t size) {
    this->_vao = this->_api->createVertexArray(vertices, size);
}
void Mesh::setIndices(int* indices, size_t size) {
    this->_vao->bindIndices(indices, size);
}
void Mesh::init() {}
void Mesh::update(float dt) {}
void Mesh::render() {
    this->_vao->draw();
}

Renderer::Renderer(GraphicsAPI* api) {
    this->_api = api;
}
Renderer::~Renderer() {
    delete this->shader;
}
void Renderer::setShader(const char* vPath, const char* fPath) {
    this->shader = this->_api->createShader(vPath, fPath);
}
void Renderer::init() {}
void Renderer::update(float dt) {}
void Renderer::render() {
    this->shader->use();
    this->material->albedo->activate(this->shader, "albedo", this->material->unit);
    this->mesh->render();
}

Transform::Transform(GraphicsAPI* api) {
    this->_api = api;
}
Transform::~Transform() {
    delete this->_api;
}
void Transform::init() {}
void Transform::update(float dt) {}
void Transform::render() {}
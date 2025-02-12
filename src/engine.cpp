#include <engine.hpp>

using namespace Engine;

Material::Material(Graphics::GraphicsAPI* api) : _api{api} {}
void Material::setShader(const char* vertexPath, const char* fragmentPath) {
    this->shader = this->_api->createShader(vertexPath, fragmentPath);
}
void Material::setAlbedo(const char* path) {
    this->albedo = this->_api->createTexture2D(path);
}
void Material::init() {}
void Material::update(float dt) {}
void Material::render() {
    this->shader->use();
    if (this->albedo) this->albedo->activate(this->shader, "albedo", this->unit % 16);
}

Mesh::Mesh(Graphics::GraphicsAPI* api) : _api{api} {}
void Mesh::setVertices(Graphics::Vertex* vertices, size_t size) {
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

Renderer::Renderer(Graphics::GraphicsAPI* api) : _api{api} {}
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
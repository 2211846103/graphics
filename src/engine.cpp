#include <engine.hpp>

using namespace Engine;

void Material::setShader(const char* vertexPath, const char* fragmentPath) {
    this->_shader = this->graphicsAPI->createShader(vertexPath, fragmentPath);
}
void Material::setAlbedo(const char* path) {
    this->_albedo = this->graphicsAPI->createTexture2D(path);
}
void Material::init() {}
void Material::update(float dt) {}
void Material::render() {
    this->_shader->use();
    if (this->_albedo) this->_albedo->activate(this->_shader, "albedo", this->unit % 16);
}

void Mesh::setVertices(Graphics::Vertex* vertices, size_t size) {
    this->_vao = this->graphicsAPI->createVertexArray(vertices, size);
}
void Mesh::setIndices(int* indices, size_t size) {
    this->_vao->bindIndices(indices, size);
}
void Mesh::init() {}
void Mesh::update(float dt) {}
void Mesh::render() {
    this->_vao->draw();
}
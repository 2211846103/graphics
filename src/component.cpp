#include <component.hpp>

using namespace Engine;
using namespace Graphics;

Component::Component(GameObject* obj) : gameObject{obj} {}

Mesh::Mesh(GameObject* obj) : Component{obj} {}

Mesh::~Mesh() {
    delete this->_vao;
}

void Mesh::setVertices(Vertex* vertices, size_t size) {
    this->_vao = this->gameObject->api->createVertexArray(vertices, size);
}

void Mesh::setIndices(int* indices, size_t size) {
    this->_vao->bindIndices(indices, size);
}

void Mesh::render() {
    this->_vao->draw();
}

Renderer::Renderer(GameObject* obj) : Component{obj} {}

Renderer::~Renderer() {
    delete this->shader;
}

void Renderer::setShader(const char* vPath, const char* fPath) {
    this->shader = this->gameObject->api->createShader(vPath, fPath);
}

void Renderer::update(float dt) {
    Transform* transform = this->gameObject->getComponent<Transform>();
    Mat4 model = transform->getModel();

    Camera* camera = SceneManager::getCurrentScene()->getActiveCamera()->getComponent<Camera>();
    Mat4 view = camera->getView();
    Mat4 projection = camera->getProjection();

    this->shader->use();
    this->shader->setUniform("model", model);
    this->shader->setUniform("view", view);
    this->shader->setUniform("projection", projection);
}

void Renderer::render() {
    this->shader->use();
    Mesh* mesh = this->gameObject->getComponent<Mesh>();
    mesh->material->albedo->activate(this->shader, "albedo", mesh->material->unit);
    mesh->render();
}

Transform::Transform(GameObject* obj) : Component{obj} {}

Mat4& Transform::getModel() {
    return this->_model;
}

void Transform::update(float dt) {
    this->_model = Mat4::identity();
    this->_model = Mat4::translation(this->_model, this->position);
    this->_model = Mat4::rotation(this->_model, glm::radians(this->rotation.x()), Vec3(1, 0, 0));
    this->_model = Mat4::rotation(this->_model, glm::radians(this->rotation.y()), Vec3(0, 1, 0));
    this->_model = Mat4::rotation(this->_model, glm::radians(this->rotation.z()), Vec3(0, 0, 1));
    this->_model = Mat4::scale(this->_model, this->scale);
}

Camera::Camera(GameObject* obj) : Component{obj} {}

Mat4& Camera::getView() {
    return this->_view;
}
Mat4& Camera::getProjection() {
    return this->_projection;
}

void Camera::viewUpdate() {
    this->_view = Mat4::identity();

    Transform* transform = this->gameObject->getComponent<Transform>();

    this->_view = Mat4::translation(this->_view, transform->position);
    this->_view = Mat4::rotation(this->_view, transform->rotation.x(), Vec3(1, 0, 0));
    this->_view = Mat4::rotation(this->_view, transform->rotation.y(), Vec3(0, 1, 0));
    this->_view = Mat4::rotation(this->_view, transform->rotation.z(), Vec3(0, 0, 1));

    this->_view = glm::lookAt(transform->position.data, transform->position.data + this->cameraTarget.data, this->up.data);
}

void Camera::projectionUpdate() {
    this->_projection = glm::perspective(glm::radians(this->fov), this->aspect, this->near, this->far);
}

void Camera::update(float dt) {
    this->viewUpdate();
    this->projectionUpdate();
}
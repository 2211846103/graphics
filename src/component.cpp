#include <component.hpp>

using namespace Engine;
using namespace Graphics;

Component::Component(GameObject* obj) : gameObject{obj} {}

Mesh::Mesh(GameObject* obj) : Component{obj} {
    this->material = new Material(this->gameObject->api);
    this->_vao = this->gameObject->api->createVertexArray();
}

Mesh::~Mesh() {
    delete this->_vao;
    delete this->material;
}

void Mesh::setVertices(Vertex* vertices, size_t size) {
    this->_vao->bindVertices(vertices, size);
}

void Mesh::setIndices(int* indices, size_t size) {
    this->_vao->bindIndices(indices, size);
}

void Mesh::applyToShader(Shader* shader) {
    this->material->albedo->activate(shader, "material.diffuse", 0);
    this->material->specular->activate(shader, "material.specular", 1);
    shader->setUniform("material.shininess", this->material->shininess);
}

void Mesh::render() {
    this->_vao->draw();
}

Renderer::Renderer(GameObject* obj) : Component{obj} {
    setShader("../res/shaders/shader.vert", "../res/shaders/shader.frag");
}

Renderer::~Renderer() {
    delete this->shader;
}

void Renderer::setShader(const char* vPath, const char* fPath) {
    if (this->shader) delete this->shader;
    this->shader = this->gameObject->api->createShader(vPath, fPath);
}

void Renderer::update(float dt) {
    this->gameObject->getComponent<Transform>()->applyToShader(this->shader);
    this->gameObject->getComponent<Mesh>()->applyToShader(this->shader);
    SceneManager::getCurrentScene()->getActiveCamera()->getComponent<Camera>()->applyToShader(this->shader);
    SceneManager::getCurrentScene()->getLights()[0]->getComponent<Light>()->applyToShader(this->shader);
}

void Renderer::render() {
    this->shader->use();
    Mesh* mesh = this->gameObject->getComponent<Mesh>();
    if (mesh->material->albedo) mesh->material->albedo->activate(this->shader, "albedo", mesh->material->unit);
    mesh->render();
}

Transform::Transform(GameObject* obj) : Component{obj} {
    this->_model = Mat4::identity();
}

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

void Transform::applyToShader(Shader* shader) {
    Mat4 model = this->getModel();
    Mat4 normalModel = model.inverse().transpose();

    shader->setUniform("model", model);
    shader->setUniform("normalModel", normalModel);
}

Camera::Camera(GameObject* obj) : Component{obj} {}

Mat4& Camera::getView() {
    return this->_view;
}
Mat4& Camera::getProjection() {
    return this->_projection;
}

void Camera::viewUpdate() {
    Transform* transform = this->gameObject->getComponent<Transform>();

    this->direction = (transform->position - this->_target).normalize();
    this->right = (Vec3(0, 1, 0).cross(direction));
    this->up = this->direction.cross(this->right);
    
    this->_target = transform->position - this->front;
    this->_view = Mat4::lookAt(transform->position, this->_target, this->up);
}

/*void Camera::projectionUpdate() {
    int width, height;
    this->gameObject->api->getDimensions(&width, &height);
    this->aspect = width / (float) height;
    this->_projection = glm::perspective(glm::radians(this->fov), this->aspect, this->near, this->far);
}

void Camera::update(float dt) {
    this->viewUpdate();
    this->projectionUpdate();
}

void Camera::applyToShader(Shader* shader) {
    Vec3 position = this->gameObject->getComponent<Transform>()->position;
    Mat4 view = this->getView();
    Mat4 projection = this->getProjection();

    shader->setUniform("view", view);
    shader->setUniform("projection", projection);
    shader->setUniform("cameraPos", position);
}*/

PerspectiveCamera::PerspectiveCamera(GameObject* obj) : Camera{obj} {
    this->_view = Mat4::identity();
    this->_projection = Mat4::identity();
    this->front = Vec3(0, 0, -1);
    int width, height;
    this->gameObject->api->getDimensions(&width, &height);
    this->aspect = width / (float) height;
}

void PerspectiveCamera::projectionUpdate() {
    int width, height;
    this->gameObject->api->getDimensions(&width, &height);
    this->aspect = width / (float) height;
    this->_projection = glm::perspective(glm::radians(this->fov), this->aspect, this->near, this->far);
}

void PerspectiveCamera::update(float dt) {
    this->viewUpdate();
    this->projectionUpdate();
}

void PerspectiveCamera::applyToShader(Shader* shader) {
    Vec3 position = this->gameObject->getComponent<Transform>()->position;
    Mat4 view = this->getView();
    Mat4 projection = this->getProjection();

    shader->setUniform("view", view);
    shader->setUniform("projection", projection);
    shader->setUniform("cameraPos", position);
}

OrthographicCamera::OrthographicCamera(GameObject* obj) : Camera{obj} {
    this->_view = Mat4::identity();
    this->_projection = Mat4::identity();
    this->front = Vec3(0, 0, -1);
}

void OrthographicCamera::projectionUpdate() {
    int width, height;
    this->gameObject->api->getDimensions(&width, &height);
    this->_projection = glm::ortho(this->left, this->right, this->bottom, this->top, this->near, this->far);
}

void OrthographicCamera::update(float dt) {
    this->viewUpdate();
    this->projectionUpdate();
}

void OrthographicCamera::applyToShader(Shader* shader) {
    Vec3 position = this->gameObject->getComponent<Transform>()->position;
    Mat4 view = this->getView();
    Mat4 projection = this->getProjection();

    shader->setUniform("view", view);
    shader->setUniform("projection", projection);
    shader->setUniform("cameraPos", position);
}

Light::Light(GameObject* obj) : Component{obj} {
    this->ambient = {0.2, 0.2, 0.2};
    this->diffuse = {0.5, 0.5, 0.5};
    this->specular = {1.0, 1.0, 1.0};
}

void Light::applyToShader(Shader* shader) {
    Vec3 position = this->gameObject->getComponent<Transform>()->position;

    shader->setUniform("light.ambient", this->ambient);
    shader->setUniform("light.diffuse", this->diffuse);
    shader->setUniform("light.specular", this->specular);
    shader->setUniform("light.position", position);
}
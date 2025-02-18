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
    Transform* transform = this->gameObject->getComponent<Transform>();
    Mat4 model = transform->getModel();
    Mat4 normalModel = model.inverse().transpose();

    Camera* camera = SceneManager::getCurrentScene()->getActiveCamera()->getComponent<Camera>();
    Mat4 view = camera->getView();
    Mat4 projection = camera->getProjection();

    Material* material = this->gameObject->getComponent<Mesh>()->material;

    Light* light = SceneManager::getCurrentScene()->getLights()[0]->getComponent<Light>();
    Transform* lightTransform = SceneManager::getCurrentScene()->getLights()[0]->getComponent<Transform>();

    Transform* cameraTransform = SceneManager::getCurrentScene()->getActiveCamera()->getComponent<Transform>();

    this->shader->use();
    this->shader->setUniform("model", model);
    this->shader->setUniform("view", view);
    this->shader->setUniform("projection", projection);
    this->shader->setUniform("normalModel", normalModel);

    material->albedo->activate(this->shader, "material.diffuse", 0);
    material->specular->activate(this->shader, "material.specular", 1);
    this->shader->setUniform("material.shininess", material->shininess);

    this->shader->setUniform("light.ambient", light->ambient);
    this->shader->setUniform("light.diffuse", light->diffuse);
    this->shader->setUniform("light.specular", light->specular);
    this->shader->setUniform("light.position", lightTransform->position);

    this->shader->setUniform("cameraPos", cameraTransform->position);
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

Camera::Camera(GameObject* obj) : Component{obj} {
    this->_view = Mat4::identity();
    this->_projection = Mat4::identity();
    this->front = Vec3(0, 0, -1);
    int width, height;
    this->gameObject->api->getDimensions(&width, &height);
    this->aspect = width / (float) height;
}

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

void Camera::projectionUpdate() {
    int width, height;
    this->gameObject->api->getDimensions(&width, &height);
    this->aspect = width / (float) height;
    this->_projection = glm::perspective(glm::radians(this->fov), this->aspect, this->near, this->far);
}

void Camera::update(float dt) {
    this->viewUpdate();
    this->projectionUpdate();
}

Light::Light(GameObject* obj) : Component{obj} {
    this->ambient = {1, 1, 1};
    this->diffuse = {1, 1, 1};
    this->specular = {1.0, 1.0, 1.0};
}
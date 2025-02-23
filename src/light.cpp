#include <light.hpp>

using namespace Engine;

DirectionalLight::DirectionalLight(GameObject* obj) : Light(obj) {}

PointLight::PointLight(GameObject* obj) : Light(obj) {}

SpotLight::SpotLight(GameObject* obj) : Light(obj) {}
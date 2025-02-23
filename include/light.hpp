#pragma once

#include <component.hpp>

namespace Engine {
    class DirectionalLight : public Light {
        public:
            Vec3 direction;

            DirectionalLight(GameObject* obj);
    };

    class PointLight : public Light {
        public:
            PointLight(GameObject* obj);
    };

    class SpotLight : public Light {
        public:
            Vec3 direction;
            float cutOffAngle;

            SpotLight(GameObject* obj);
    };
}
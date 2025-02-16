#pragma once

#include <component.hpp>

namespace Engine {
    class PlaneMesh : public Mesh {
        public:
            PlaneMesh(GameObject* obj);
    };

    class CubeMesh : public Mesh {
        public:
            CubeMesh(GameObject* obj);
    };
}
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

    class SphereMesh : public Mesh {
        private:
            std::vector<Vertex> _generateVertices();
            std::vector<int> _generateIndices();
            void _generateMesh();
            int _numOfSeg;
            int _numLat = 32;
            int _numLon = 64;
        
        public:
            SphereMesh(GameObject* obj);

            void setLongitudeCount(int numLon);
            void setLatitudeCount(int numLat);
            void setSegmentCount(int numLon, int numLat);

            int getLongitudeCount();
            int getLatitudeCount();
    };
}
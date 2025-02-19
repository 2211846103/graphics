#include <mesh.hpp>
#include <cmath>

using namespace Engine;

PlaneMesh::PlaneMesh(GameObject* obj) : Mesh(obj) {
    Vertex vertices[] = {
        {{-0.5f, -0.5f, 0},  {0, 0, -1}, {0.0f, 0.0f}},
        {{ 0.5f, -0.5f, 0},  {0, 0, -1}, {1.0f, 0.0f}},
        {{ 0.5f,  0.5f, 0},  {0, 0, -1}, {1.0f, 1.0f}},
        {{-0.5f,  0.5f, 0},  {0, 0, -1}, {0.0f, 1.0f}}
    };

    int indices[] = {
        0,  1,  2,
        0,  2,  3
    };

    this->setVertices(vertices, sizeof(vertices));
    this->setIndices(indices, sizeof(indices));
}

CubeMesh::CubeMesh(GameObject* obj) : Mesh(obj) {
    Vertex vertices[] = {
        {{-0.5f, -0.5f, -0.5f},  { 0,  0, -1}, {0.0f, 0.0f}},
        {{ 0.5f, -0.5f, -0.5f},  { 0,  0, -1}, {1.0f, 0.0f}},
        {{ 0.5f,  0.5f, -0.5f},  { 0,  0, -1}, {1.0f, 1.0f}},
        {{-0.5f,  0.5f, -0.5f},  { 0,  0, -1}, {0.0f, 1.0f}},

        {{-0.5f, -0.5f,  0.5f},   {0,  0,  1}, {0.0f, 0.0f}},
        {{ 0.5f, -0.5f,  0.5f},  { 0,  0,  1}, {1.0f, 0.0f}},
        {{ 0.5f,  0.5f,  0.5f},  { 0,  0,  1}, {1.0f, 1.0f}},
        {{-0.5f,  0.5f,  0.5f},  { 0,  0,  1}, {0.0f, 1.0f}},

        {{-0.5f,  0.5f,  0.5f},  {-1,  0,  0}, {1.0f, 0.0f}},
        {{-0.5f,  0.5f, -0.5f},  {-1,  0,  0}, {1.0f, 1.0f}},
        {{-0.5f, -0.5f, -0.5f},  {-1,  0,  0}, {0.0f, 1.0f}},
        {{-0.5f, -0.5f,  0.5f},  {-1,  0,  0}, {0.0f, 0.0f}},

        {{ 0.5f,  0.5f,  0.5f},  { 1,  0,  0}, {1.0f, 0.0f}},
        {{ 0.5f,  0.5f, -0.5f},  { 1,  0,  0}, {1.0f, 1.0f}},
        {{ 0.5f, -0.5f, -0.5f},  { 1,  0,  0}, {0.0f, 1.0f}},
        {{ 0.5f, -0.5f,  0.5f},  { 1,  0,  0}, {0.0f, 0.0f}},

        {{-0.5f, -0.5f, -0.5f},  { 0, -1,  0}, {0.0f, 1.0f}},
        {{ 0.5f, -0.5f, -0.5f},  { 0, -1,  0}, {1.0f, 1.0f}},
        {{ 0.5f, -0.5f,  0.5f},  { 0, -1,  0}, {1.0f, 0.0f}},
        {{-0.5f, -0.5f,  0.5f},  { 0, -1,  0}, {0.0f, 0.0f}},

        {{-0.5f,  0.5f, -0.5f},  { 0,  1,  0}, {0.0f, 1.0f}},
        {{ 0.5f,  0.5f, -0.5f},  { 0,  1,  0}, {1.0f, 1.0f}},
        {{ 0.5f,  0.5f,  0.5f},  { 0,  1,  0}, {1.0f, 0.0f}},
        {{-0.5f,  0.5f,  0.5f},  { 0,  1,  0}, {0.0f, 0.0f}}
    };

    int indices[] = {
        0,  1,  2,
        0,  2,  3,

        4,  5,  6,
        4,  6,  7,

        8,  9, 10,
        8, 10, 11,

       12, 13, 14,
       12, 14, 15,

       16, 17, 18,
       16, 18, 19,

       20, 21, 22,
       20, 22, 23
   };

    this->setVertices(vertices, sizeof(vertices));
    this->setIndices(indices, sizeof(indices));
}

std::vector<Vertex> SphereMesh::_generateVertices() {
    std::vector<Vertex> vertices;
    const float radius = 0.5;
    
    for (int lat = 0; lat <= this->_numLat; lat++) {
        float theta = M_PI * (-0.5f + (float)lat / this->_numLat);
        float cosTheta = cos(theta);
        float sinTheta = sin(theta);

        for (int lon = 0; lon <= this->_numLon; lon++) {
            float phi = 2 * M_PI * ((float)lon / this->_numLon);
            float cosPhi = cos(phi);
            float sinPhi = sin(phi);

            Vertex v;
            v.position.data.x = radius * cosTheta * cosPhi;
            v.position.data.y = radius * sinTheta;
            v.position.data.z = radius * cosTheta * sinPhi;

            v.normal = v.position.normalize();

            v.uv.data.x = phi / (M_PI * 2);
            v.uv.data.y = (theta + M_PI_2) / M_PI;

            vertices.push_back(v);
        }
    }

    return vertices;
}

std::vector<int> SphereMesh::_generateIndices() {
    std::vector<int> indices;

    for (int lat = 0; lat <= this->_numLat; lat++) {
        for (int lon = 0; lon <= this->_numLon; lon++) {
            int A = lat * (this->_numLon + 1) + lon;
            int B = A + 1;
            int C = (lat + 1) * (this->_numLon + 1) + lon;
            int D = C + 1;

            indices.push_back(A);
            indices.push_back(C);
            indices.push_back(B);

            indices.push_back(B);
            indices.push_back(C);
            indices.push_back(D);
        }
    }

    return indices;
}

void SphereMesh::_generateMesh() {
    std::vector<Vertex> vertices = _generateVertices();
    std::vector<int> indices = _generateIndices();

    this->setVertices(vertices.data(), vertices.size() * sizeof(Vertex));
    this->setIndices(indices.data(), indices.size() * sizeof(int));
}

SphereMesh::SphereMesh(GameObject* obj) : Mesh(obj) {
    this->_generateMesh();
}

void SphereMesh::setLongitudeCount(int numLon) {
    this->_numLon = numLon;
    this->_generateMesh();
}

void SphereMesh::setLatitudeCount(int numLat) {
    this->_numLat = numLat;
    this->_generateMesh();
}

void SphereMesh::setSegmentCount(int numLon, int numLat) {
    this->_numLon = numLon;
    this->_numLat = numLat;

    this->_generateMesh();
}

int SphereMesh::getLongitudeCount() {
    return this->_numLon;
}

int SphereMesh::getLatitudeCount() {
    return this->_numLat;
}
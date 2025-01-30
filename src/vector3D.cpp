#include <vector3D.hpp>

using namespace Graphics;

Vertex::Vertex(Vector3D pos, Vector3D col, Vector3D nor, Vector2D uv) {
    this->position = pos;
    this->color = col;
    this->normal = nor;
    this->uv = uv;
}

float* Vertex::toFloat(Vertex* verArr[], int numOfVertices) {
    int size = floatPerVer * numOfVertices;
    float* verFloatArr = new float[size];
    for (int i = 0; i < numOfVertices; i++) {
        verFloatArr[i * floatPerVer] = verArr[i]->color.x;
        verFloatArr[i * floatPerVer + 1] = verArr[i]->color.y;
        verFloatArr[i * floatPerVer + 2] = verArr[i]->color.z;
        verFloatArr[i * floatPerVer + 3] = verArr[i]->position.x;
        verFloatArr[i * floatPerVer + 4] = verArr[i]->position.y;
        verFloatArr[i * floatPerVer + 5] = verArr[i]->position.z;
        verFloatArr[i * floatPerVer + 6] = verArr[i]->normal.x;
        verFloatArr[i * floatPerVer + 7] = verArr[i]->normal.y;
        verFloatArr[i * floatPerVer + 8] = verArr[i]->normal.z;
        verFloatArr[i * floatPerVer + 9] = verArr[i]->uv.x;
        verFloatArr[i * floatPerVer + 10] = verArr[i]->uv.y;
    }
    return verFloatArr;
}
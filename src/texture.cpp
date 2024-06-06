#include <texture.hpp>

using namespace Graphics;

template <typename T>
TextureParam<T>::TextureParam(TextureParamName name, T value) {
    this->name = name;
    this->value = value;
}
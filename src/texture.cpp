#include <texture.hpp>

using namespace Graphics;

template <typename T>
TextureParam::TextureParam(TextureParamName name, T value) {
    this->name = name;
    this->value = value;
}

void TextureConfiguration::add(TextureParam* parameter) {
    auto iter = std::find_if(this->_parameters.begin(), this->_parameters.end(), [&](TextureParam* param) {
        return param->name == parameter->name;
    });
    if (iter != this->_parameters.end()) {
        return;
    }

    this->_parameters.push_back(parameter);
}

void TextureConfiguration::remove(TextureParamName name) {
    auto iter = std::remove_if(this->_parameters.begin(), this->_parameters.end(), [&](TextureParam* param) {
        return param->name == name;
    });

    this->_parameters.erase(iter, this->_parameters.end());
}

template <typename T>
T TextureConfiguration::get(TextureParamName name) {
    auto iter = std::find(this->_parameters.begin(), this->_parameters.end(), [&](TextureParam* param) {
        return param->name == name;
    });

    return (*iter)->value;
}
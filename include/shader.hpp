#pragma once

#include <glad/glad.h>
#include <math.hpp>
#include <fstream>
#include <iostream>

namespace Graphics {

    class Shader {
        public:
            virtual ~Shader() = default;

            virtual void use() = 0;

            template <typename T>
            void setUniform(const char* name, T value) {};
    };

    class OpenGLShader: public Shader {
        private:
            unsigned int _shaderProgram;
            unsigned int _vertex;
            unsigned int _fragment;
        public:

            OpenGLShader(const char* vShaderPath, const char* fShaderPath);
            ~OpenGLShader() override;

            void use() override;

            template <typename T>
            void setUniform(const char* name, T value);
    };
}
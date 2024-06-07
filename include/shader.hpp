#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <iostream>
#include <math.h>

namespace Graphics {

    class Shader {
        public:
            virtual ~Shader() = default;

            virtual void useShader() = 0;
            virtual void setUniform(const char* uniName) = 0;
    };

    class OpenGLShader: public Shader {
        private:
            unsigned int _shaderProgram;
            unsigned int _vertex;
            unsigned int _fragment;
        public:

            OpenGLShader(const char* vShaderPath, const char* fShaderPath);
            ~OpenGLShader() override;

            void useShader() override;
            void setUniform(const char* uniName) override;

    };
}
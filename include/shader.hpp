#pragma once

#include <glad/glad.h>
#include <fstream>
#include <iostream>

namespace Graphics {

    class Shader {
        public:
            virtual ~Shader() = default;

            virtual void useShader() = 0;
    };

    class OpenGLShader: public Shader {
        public:
            unsigned int shaderProgram;
            unsigned int vertex;
            unsigned int fragment;

            OpenGLShader(const char* vShaderPath, const char* fShaderPath);
            ~OpenGLShader() override;

            void useShader() override;
    };
}
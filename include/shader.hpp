#pragma once

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace Graphics {

    class Shader {};

    class OpenGLShader: public Shader {
        public:
            unsigned int shaderProgram;
            unsigned int vertex;
            unsigned int fragment;

            OpenGLShader(const char* vShaderPath, const char* fShaderPath);
            ~OpenGLShader();

            void useShader();

    };
}
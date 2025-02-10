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

            virtual void setUniform(const char* name, int value) = 0;
            virtual void setUniform(const char* name, float value) = 0;
            virtual void setUniform(const char* name, bool value) = 0;
            virtual void setUniform(const char* name, Math::Vec2& value) = 0;
            virtual void setUniform(const char* name, Math::Vec3& value) = 0;
            virtual void setUniform(const char* name, glm::vec4& value) = 0;
            virtual void setUniform(const char* name, glm::mat4& value) = 0;
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

            void setUniform(const char* name, int value) override;
            void setUniform(const char* name, float value) override;
            void setUniform(const char* name, bool value) override;
            void setUniform(const char* name, Math::Vec2& value) override;
            void setUniform(const char* name, Math::Vec3& value) override;
            void setUniform(const char* name, glm::vec4& value) override;
            void setUniform(const char* name, glm::mat4& value) override;
    };
}
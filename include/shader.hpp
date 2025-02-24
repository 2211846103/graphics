#pragma once

#include <glad/glad.h>
#include <math.hpp>
#include <file.hpp>
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
            virtual void setUniform(const char* name, Math::Vec4& value) = 0;
            virtual void setUniform(const char* name, Math::Mat4& value) = 0;
    };

    class OpenGLShader: public Shader {
        private:
            unsigned int _vertex;
            unsigned int _fragment;

        protected:
            unsigned int _shaderProgram;
        
        public:
            OpenGLShader(const char* vShaderPath, const char* fShaderPath);
            ~OpenGLShader();

            void use() override;

            void setUniform(const char* name, int value) override;
            void setUniform(const char* name, float value) override;
            void setUniform(const char* name, bool value) override;
            void setUniform(const char* name, Math::Vec2& value) override;
            void setUniform(const char* name, Math::Vec3& value) override;
            void setUniform(const char* name, Math::Vec4& value) override;
            void setUniform(const char* name, Math::Mat4& value) override;
    };

    class ComputeShader {
        public:
            virtual ~ComputeShader() = default;

            virtual void dispatch(int numGroupsX, int numGroupsY, int numGroupsZ) = 0;

            virtual void setUniform(const char* name, int value) = 0;
            virtual void setUniform(const char* name, float value) = 0;
            virtual void setUniform(const char* name, bool value) = 0;
            virtual void setUniform(const char* name, Math::Vec2& value) = 0;
            virtual void setUniform(const char* name, Math::Vec3& value) = 0;
            virtual void setUniform(const char* name, Math::Vec4& value) = 0;
            virtual void setUniform(const char* name, Math::Mat4& value) = 0;
    };

    class OpenGLComputeShader : public ComputeShader {
        private:
            unsigned int _compute;
            unsigned int _shaderProgram;
        
        public:
            OpenGLComputeShader(const char* shaderPath);
            ~OpenGLComputeShader();

            void dispatch(int numGroupsX, int numGroupsY, int numGroupsZ) override;

            void setUniform(const char* name, int value) override;
            void setUniform(const char* name, float value) override;
            void setUniform(const char* name, bool value) override;
            void setUniform(const char* name, Math::Vec2& value) override;
            void setUniform(const char* name, Math::Vec3& value) override;
            void setUniform(const char* name, Math::Vec4& value) override;
            void setUniform(const char* name, Math::Mat4& value) override;
    };
}
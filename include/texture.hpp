#pragma once

#include <glad/glad.h>
#include <stb_image.h>
#include <dirent.h>
#include <vector>
#include <string>
#include <iostream>

namespace Graphics {
    class TextureAPI {
        public:
            virtual ~TextureAPI() = default;

            virtual void bind2D() = 0;
            virtual void bind3D() = 0;
            virtual void bindCube() = 0;
            virtual void unbind() = 0;

            virtual void load2D(const char* path, int* width, int* height) = 0;
            virtual void load3D(const char* dir, int* width, int* height, int layers) = 0;
            virtual void loadCube() = 0;
    };

    class OpenGLTexture : public TextureAPI {
        private:
            unsigned int _id;
            GLenum _target;

        public:
            OpenGLTexture();
            ~OpenGLTexture();

            void bind2D() override;
            void bind3D() override;
            void bindCube() override;
            void unbind() override;

            void load2D(const char* path, int* width, int* height) override;
            void load3D(const char* dir, int* width, int* height, int layers) override;
            void loadCube() override;
    };
}
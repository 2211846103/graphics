#pragma once

#include <glad/glad.h>
#include <stb_image.h>
#include <dirent.h>
#include <vector>
#include <cstring>
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
            virtual void load3D(const char* path[], size_t size, int* width, int* height, int* depth) = 0;
            virtual void loadCube(const char* path[], size_t size, int* width, int* height) = 0;
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
            void load3D(const char* path[], size_t size, int* width, int* height, int* depth) override;
            void loadCube(const char* path[], size_t size, int* width, int* height) override;
    };

    class Texture2D {
      private:
          TextureAPI* _api;

      public:
          int width, height;

          Texture2D(TextureAPI* api);

          void bind();
          void unbind();
          void load(const char* path);
    };

    class Texture3D {
      private:
          TextureAPI* _api;

      public:
          int width, height, depth;

          Texture3D(TextureAPI* api);

          void bind();
          void unbind();
          void load(const char* path[], size_t size = 0);
    };

    class TextureCube {
        private:
            TextureAPI* _api;

        public:
            int width, height;

            TextureCube(TextureAPI* api);

            void bind();
            void unbind();
            void load(const char* path[], size_t size = 0);
    };
}

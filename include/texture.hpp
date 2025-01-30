#pragma once

#include <glad/glad.h>
#include <stb_image.h>
#include <dirent.h>
#include <vector>
#include <cstring>
#include <iostream>

namespace Graphics {
    class TextureConfig {
        public:
            int base_level;
    };

    class TextureConfigBuilder {
        public:
            int base_level = 0;

            TextureConfigBuilder* setBaseLevel(int level);

            TextureConfig* build();
    };

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

            virtual void loadConfig(TextureConfig* config) = 0;
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

            void loadConfig(TextureConfig* config) override;
    };

    class Texture {
        protected:
            TextureAPI* _api;

        public:
            int width, height;

            virtual void bind() {};
            virtual void unbind() {};
    };

    class Texture2D : public Texture {
      public:
          Texture2D(TextureAPI* api);

          void bind() override;
          void unbind() override;
          void load(const char* path);
    };

    class Texture3D : public Texture {
      private:
          TextureAPI* _api;

      public:
          int width, height, depth;

          Texture3D(TextureAPI* api);

          void bind() override;
          void unbind() override;
          void load(const char* path[], size_t size = 0);
    };

    class TextureCube : public Texture {
        private:
            TextureAPI* _api;

        public:
            int width, height;

            TextureCube(TextureAPI* api);

            void bind() override;
            void unbind() override;
            void load(const char* path[], size_t size = 0);
    };
}

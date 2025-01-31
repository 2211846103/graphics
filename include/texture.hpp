#pragma once

#include <glad/glad.h>
#include <stb_image.h>
#include <dirent.h>
#include <vector>
#include <cstring>
#include <iostream>

#include <shader.hpp>

namespace Graphics {
    enum TextureChannel {
        RED, GREEN, BLUE, ALPHA, ZERO, ONE
    };

    enum TextureFilter {
        LINEAR, NEAREST, NEAREST_MIPMAP_NEAREST,
        NEAREST_MIPMAP_LINEAR, LINEAR_MIPMAP_NEAREST,
        LINEAR_MIPMAP_LINEAR
    };

    enum TextureWrap {
        CLAMP_TO_BORDER, CLAMP_TO_EDGE,
        MIRRORED_REPEAT, REPEAT
    };

    class TextureConfig {
        public:
            int base_level = 0;
            TextureFilter min_filter = NEAREST;
            TextureFilter mag_filter = LINEAR;
            float lod_bias = 0.0;
            float min_lod = -1000;
            float max_lod = 1000;
            int max_level = 1000;
            TextureWrap wrap_x = REPEAT;
            TextureWrap wrap_y = REPEAT;
            TextureWrap wrap_z = REPEAT;
            TextureChannel swizzle_r = RED;
            TextureChannel swizzle_g = GREEN;
            TextureChannel swizzle_b = BLUE;
            TextureChannel swizzle_a = ALPHA;

            ~TextureConfig() = delete;
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

            virtual void generateMipmap() = 0;

            virtual void activate(int unit) = 0;

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

            void generateMipmap() override;

            void activate(int unit) override;

            void loadConfig(TextureConfig* config) override;
    };

    class Texture {
        protected:
            TextureAPI* _api;
            bool isConfigLoaded = false;

        public:
            int width, height;
            TextureConfig* config;

            virtual void bind() = 0;
            virtual void unbind() = 0;
            void activate(Shader* shader, const char* uniName, int unit);
    };

    class Texture2D : public Texture {
      public:
          Texture2D(TextureAPI* api);

          void bind() override;
          void unbind() override;
          void mipmap();
          void load(const char* path);
    };

    class Texture3D : public Texture {
      public:
          int width, height, depth;

          Texture3D(TextureAPI* api);

          void bind() override;
          void unbind() override;
          void load(const char* path[], size_t size = 0);
    };

    class TextureCube : public Texture {
        public:
            int width, height;

            TextureCube(TextureAPI* api);

            void bind() override;
            void unbind() override;
            void load(const char* path[], size_t size = 0);
    };
}

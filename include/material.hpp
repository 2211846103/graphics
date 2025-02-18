#pragma once

#include <graphics_api.hpp>

namespace Engine {
    using namespace Graphics;

    class Material {
        private:
            GraphicsAPI* _api;
    
        public:
            unsigned char unit = 0;

            float shininess;
            Texture2D* albedo = nullptr;
            Texture2D* specular = nullptr;
    
            Material(GraphicsAPI* api);
            ~Material();

            void setAlbedo(Vec3 color);
            void setAlbedo(const char* path);
            void setSpecular(Vec3 color);
            void setSpecular(const char* path);
    };
}
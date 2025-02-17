#pragma once

#include <graphics_api.hpp>

namespace Engine {
    using namespace Graphics;

    class Material {
        private:
            GraphicsAPI* _api;
    
        public:
            unsigned char unit = 0;

            Vec3 ambient;
            Vec3 diffuse;
            Vec3 specular;
            float shininess;

            Texture2D* albedo = nullptr;
    
            Material(GraphicsAPI* api);
            ~Material();

            void setAlbedo(const char* path);
    };
}
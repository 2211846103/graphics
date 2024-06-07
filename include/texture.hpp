#pragma once

#include <glad/glad.h>
#include <stb_image.h>
#include <variant>
#include <vector>
#include <algorithm>

namespace Graphics {
    enum TextureTarget {
        T2D, T3D, TCube,
        T2DArray, T3DArray, TMultiSample,
        TCompressed, TDepth, TRenderTarget
    };

    enum TextureParamName {
        BaseLevel, LODBias, MinFilter, MagFilter,
        MinLOD, MaxLOD, MaxLevel, SwizzleR, SwizzleG,
        SwizzleB, SwizzleA, SwizzleRGBA, WrapS, WrapT, WrapR
    };

    enum TextureParamValue {
        Nearest, Linear, NearestMipmapNearest,
        NearestMipmapLinear, LinearMipmapNearest,
        LinearMipmapLinear, Red, Green, Blue, Alpha,
        Zero, One, ClampToEdge, ClampToBorder,
        MirroredRepeat, Repeat
    };

    class TextureParam {
        private:
            std::variant<TextureParamValue, float, int> _value;

        public:
            TextureParamName name;
            
            template <typename T>
            TextureParam(TextureParamName name, T value);
    };

    class TextureConfiguration {
        private:
            std::vector<TextureParam*> _parameters;

        public:
            void add(TextureParam* parameter);
            void remove(TextureParamName name);
            template <typename T>
            T get(TextureParamName name);
    };
}
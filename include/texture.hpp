#pragma once

#include <glad/glad.h>
#include <stb_image.h>

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

    template <typename T>
    class TextureParam {
        private:
            TextureParamName name;
            T value;

        public:
            TextureParam(TextureParamName name, T value);
    };
}
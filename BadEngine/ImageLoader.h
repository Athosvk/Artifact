#pragma once
#include "GLTexture.h"

namespace BadEngine
{
    class ImageLoader
    {
    public:
        ImageLoader() = delete;
        ~ImageLoader() = delete;

        static GLTexture loadPNG(const std::string& a_FilePath);
    };
}
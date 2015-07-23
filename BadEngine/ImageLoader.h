#pragma once
#include <string>
#include "GLTexture.h"

namespace BadEngine
{
    class ImageLoader
    {
    public:
        static GLTexture loadPNG(const std::string& a_FilePath);
    };
}
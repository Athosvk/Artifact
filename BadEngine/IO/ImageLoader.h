#pragma once
#include <memory>

#include "../GL/GLTexture.h"

namespace BadEngine
{
    class ImageLoader
    {
    public:
        ImageLoader() = delete;
        ~ImageLoader() = delete;

        static std::shared_ptr<GLTexture> loadPNG(const std::string& a_FilePath);
    };
}
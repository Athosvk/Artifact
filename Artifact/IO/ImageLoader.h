#pragma once
#include <memory>

#include "../GL/GLTexture.h"

namespace Artifact
{
    class ImageLoader
    {
    public:
        ImageLoader() = delete;
        ~ImageLoader() = delete;

        static std::unique_ptr<GLTexture> loadPNG(const std::string& a_FilePath);
    };
}
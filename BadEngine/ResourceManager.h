#pragma once
#include <string>

#include "TextureCache.h"

namespace BadEngine
{
    class ResourceManager
    {
    private:
        static TextureCache s_TextureCache;

    public:
        static GLTexture getTexture(const std::string& a_FilePath);
    };
}
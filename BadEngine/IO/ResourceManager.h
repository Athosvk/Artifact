#pragma once
#include <string>

#include "TextureCache.h"

namespace BadEngine
{
    class ResourceManager
    {
    private:
        TextureCache m_TextureCache;

    public:
        std::shared_ptr<GLTexture> getTexture(const std::string& a_FilePath);
    };
}
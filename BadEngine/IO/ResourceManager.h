#pragma once
#include <string>

#include "TextureCache.h"

namespace BadEngine
{
    class ResourceManager
    {
    private:
        static TextureCache m_TextureCache;

    public:
        ResourceManager() = delete;
        ~ResourceManager() = delete;
        ResourceManager(const ResourceManager& a_ResourceManager) = delete;

        static std::shared_ptr<GLTexture> getTexture(const std::string& a_FilePath);
    };
}
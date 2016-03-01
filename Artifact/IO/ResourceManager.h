#pragma once
#include <string>

#include "TextureCache.h"
#include "ResourceCache.h"
#include "../Rendering/SpriteFont.h"

namespace Artifact
{
    class ResourceManager
    {
    private:
        static TextureCache s_TextureCache;
        static ResourceCache<SpriteFont> s_FontCache;

    public:
        ResourceManager() = delete;
        ~ResourceManager() = delete;
        ResourceManager(const ResourceManager& a_ResourceManager) = delete;

        static GLTexture* getTexture(const std::string& a_FilePath);
        static SpriteFont* getFont(const std::string& a_FilePath);
    };
}
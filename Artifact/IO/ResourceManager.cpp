#include "ResourceManager.h"

namespace Artifact
{
    TextureCache ResourceManager::s_TextureCache;
    ResourceCache<SpriteFont> ResourceManager::s_FontCache;

    GLTexture* ResourceManager::getTexture(const std::string& a_FilePath)
    {
        return s_TextureCache.getTexture(a_FilePath);
    }

    SpriteFont* ResourceManager::getFont(const std::string& a_FilePath)
    {
        const int FontResolution = 64;
        SpriteFont* fontHandle = nullptr;
        if(!s_FontCache.tryGetResource(a_FilePath, fontHandle))
        {
            fontHandle = s_FontCache.emplace(a_FilePath, std::make_unique<SpriteFont>(a_FilePath.c_str(), 
                FontResolution));
        }
        return fontHandle;
    }
}
#include "ResourceManager.h"

namespace BadEngine
{
    TextureCache ResourceManager::s_TextureCache;

    GLTexture ResourceManager::getTexture(const std::string& a_FilePath)
    {
        return s_TextureCache.getTexture(a_FilePath);
    }
}
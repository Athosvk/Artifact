#include "ResourceManager.h"

namespace BadEngine
{
    TextureCache ResourceManager::m_TextureCache;

    GLTexture* ResourceManager::getTexture(const std::string& a_FilePath)
    {
        return m_TextureCache.getTexture(a_FilePath);
    }
}
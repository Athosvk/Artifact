#include "ResourceManager.h"

namespace BadEngine
{
    std::shared_ptr<GLTexture> ResourceManager::getTexture(const std::string& a_FilePath)
    {
        return m_TextureCache.getTexture(a_FilePath);
    }
}
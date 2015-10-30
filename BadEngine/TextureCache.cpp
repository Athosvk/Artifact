#include "TextureCache.h"
#include "ImageLoader.h"

namespace BadEngine
{
    TextureCache::TextureCache()
    {
    }

    TextureCache::~TextureCache()
    {
    }

    GLTexture TextureCache::getTexture(const std::string& a_FilePath)
    {
        auto iterator = m_TextureMap.find(a_FilePath);
        if(iterator == m_TextureMap.end())
        {
            auto newTexture = ImageLoader::loadPNG(a_FilePath);
            cacheTexture(a_FilePath, newTexture);
            return newTexture;
        }
        return iterator->second;
    }

    void TextureCache::cacheTexture(const std::string& a_FilePath, const GLTexture& a_Texture)
    {
        m_TextureMap.emplace(a_FilePath, a_Texture);
    }
}
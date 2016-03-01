#include "TextureCache.h"
#include "ImageLoader.h"

namespace Artifact
{
    GLTexture* TextureCache::getTexture(const std::string& a_FilePath)
    {
        std::map<const std::string, std::unique_ptr<GLTexture>>::const_iterator iterator = m_TextureMap.find(a_FilePath);
        if(iterator == m_TextureMap.end())
        {
            auto newTexture = ImageLoader::loadPNG(a_FilePath);
            auto textureHandle = newTexture.get();
            cacheTexture(a_FilePath, std::move(newTexture));
            return textureHandle;
        }
        return iterator->second.get();
    }

    void TextureCache::cacheTexture(const std::string& a_FilePath, std::unique_ptr<GLTexture>&& a_Texture)
    {
        m_TextureMap.emplace(a_FilePath, std::forward<std::unique_ptr<GLTexture>>(a_Texture));
    }
}
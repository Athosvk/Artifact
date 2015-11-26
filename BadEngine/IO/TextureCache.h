#pragma once
#include <map>
#include <memory>

#include "..\GL/GLTexture.h"

namespace BadEngine
{
    class TextureCache
    {
    private:
        std::map<const std::string, std::shared_ptr<GLTexture>> m_TextureMap;
    public:
        TextureCache();
        ~TextureCache();

        std::shared_ptr<GLTexture> getTexture(const std::string& a_FilePath);
        void cacheTexture(const std::string& a_FilePath, const std::shared_ptr<GLTexture>& a_Texture);
    };
}
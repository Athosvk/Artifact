#pragma once
#include <map>

#include "..\GL/GLTexture.h"

namespace BadEngine
{
    class TextureCache
    {
    private:
        std::map<std::string, GLTexture> m_TextureMap;
    public:
        TextureCache();
        ~TextureCache();

        GLTexture getTexture(const std::string& a_FilePath);
        void cacheTexture(const std::string& a_FilePath, const GLTexture& a_Texture);
    };
}
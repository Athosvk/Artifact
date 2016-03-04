#include <SDLMixer/SDL_mixer.h>

#include "ResourceManager.h"

namespace Artifact
{
    TextureCache ResourceManager::s_TextureCache;
    ResourceCache<SpriteFont> ResourceManager::s_FontCache;
    ResourceCache<Sound> ResourceManager::s_SoundCache;

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

    Sound* ResourceManager::getSound(const std::string& a_FilePath)
    {
        Sound* soundHandle = nullptr;
        if(!s_SoundCache.tryGetResource(a_FilePath, soundHandle))
        {
            soundHandle = s_SoundCache.emplace(a_FilePath, std::make_unique<Sound>(a_FilePath));
        }
        return soundHandle;
    }
}
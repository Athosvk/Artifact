#include "Sound.h"
#include "../ErrorHandler.h"

namespace Artifact
{
    Sound::Sound(const std::string a_FilePath)
    {
        m_SoundChunk = Mix_LoadWAV(a_FilePath.c_str());
        if(m_SoundChunk == nullptr)
        {
            throwFatalError("Could not load sound: " + std::string(Mix_GetError()));
        }
    }

    Sound::~Sound()
    {
        Mix_FreeChunk(m_SoundChunk);
    }
}
#include <exception>
#include <SDLMixer/SDL_mixer.h>

#include "Sound.h"
#include "../ErrorHandler.h"

namespace Artifact
{
    const int Sound::LoopForever = -1;
    const int Sound::PlayFailed = -1;

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

    void Sound::play(int a_LoopCount)
    {
        const int DefaultChannel = -1;
        m_CurrentChannel = Mix_PlayChannel(DefaultChannel, m_SoundChunk, a_LoopCount);
        if(m_CurrentChannel == PlayFailed)
        {
            throwFatalError("SDL_Mixer sound could not be played: " + std::string(Mix_GetError()));
        }
    }

    void Sound::stop()
    {
        Mix_HaltChannel(m_CurrentChannel);
    }

    void Sound::setVolume(unsigned a_Volume)
    {
        if(a_Volume > MIX_MAX_VOLUME)
        {
            throw std::out_of_range("Volume exceeds maximum volume");
        }
        Mix_VolumeChunk(m_SoundChunk, a_Volume);
    }
}
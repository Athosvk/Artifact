#pragma once
#include <SDLMixer/SDL_mixer.h>
#include <string>

namespace Artifact
{
    class Sound
    {
    private:
        Mix_Chunk* m_SoundChunk;

    public:
        Sound(const std::string a_FilePath);
        ~Sound();
    };
}

#pragma once
#include <SDLMixer/SDL_mixer.h>
#include <string>

namespace Artifact
{
    class Sound
    {
    public:
        static const int LoopForever;
    private:
        static const int PlayFailed;

        Mix_Chunk* m_SoundChunk;

    public:
        Sound(const std::string a_FilePath);
        ~Sound();

        void play(int a_LoopCount = 0);
        void setVolume(unsigned a_Volume);
    };
}

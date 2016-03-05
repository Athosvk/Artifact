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

        int m_CurrentChannel = -1;
        Mix_Chunk* m_SoundChunk;

    public:
        Sound(const std::string a_FilePath);
        ~Sound();

        void play(int a_LoopCount = 0);
        void stop();
        void setVolume(unsigned a_Volume);
    };
}

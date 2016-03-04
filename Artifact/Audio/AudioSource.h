#pragma once
#include "../Core/Component.h"

namespace Artifact
{
    class Sound;

    class AudioSource : public Component
    {
    private:
        bool m_Loop = false;
    public:
        Sound* Sound = nullptr;

    public:
        AudioSource(GameObject a_Entity);

        void play();
        void enableLooping();
        void disableLooping();
    };
}
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
        float Volume = 1.0f;

    public:
        explicit AudioSource(GameObject a_Entity);

        void play() const;
        void stop() const;
        void enableLooping();
        void disableLooping();
    };
}
#include "AudioSource.h"
#include "Sound.h"

namespace Artifact
{
    AudioSource::AudioSource(GameObject a_Entity)
        : Component(a_Entity)
    {
    }

    void AudioSource::play()
    {
        if(m_Loop)
        {
            Sound->play(Sound::LoopForever);
        }
        else
        {
            Sound->play();
        }
    }

    void AudioSource::enableLooping()
    {
        m_Loop = true;
    }

    void AudioSource::disableLooping()
    {
        m_Loop = false;
    }
}
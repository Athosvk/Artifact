#include <SDLMixer/SDL_mixer.h>

#include "AudioSystem.h"
#include "../ErrorHandler.h"

namespace Artifact
{
    AudioSystem::AudioSystem(EntitySystem& a_EntitySystem, MessagingSystem& a_MessagingSystem)
        : System(a_EntitySystem, a_MessagingSystem)
    {
        initialize();
    }

    AudioSystem::~AudioSystem()
    {
        Mix_CloseAudio();
        Mix_Quit();
    }

    void AudioSystem::registerListeners()
    {
    }

    void AudioSystem::initialize()
    {
        const int InitializationFailed = -1;
        if(Mix_Init(MIX_InitFlags::MIX_INIT_MP3 | MIX_InitFlags::MIX_INIT_OGG) == InitializationFailed)
        {
            throwFatalError("Could not initialize SDL_Mixer: " + std::string(Mix_GetError()));
        }

        const int DefaultChunkSize = 1024;
        if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, DefaultChunkSize))
        {
            throwFatalError("Could not open audio device: " + std::string(Mix_GetError()));
        }
    }
}
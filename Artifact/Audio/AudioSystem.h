#pragma once
#include "../Core/System.h"

namespace Artifact
{
    class AudioSystem : public System
    {
    public:
        AudioSystem(EntitySystem& a_EntitySystem, MessagingSystem& a_MessagingSystem);
        virtual ~AudioSystem() override;

        virtual void registerListeners() override;
    private:
        void initialize();
    };
}

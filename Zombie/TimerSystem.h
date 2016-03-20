#pragma once
#include <Artifact/Core/System.h>

class TimerComponent;
namespace Artifact
{
    class UpdateMessage;
}

class TimerSystem : public Artifact::System
{
public:
    TimerSystem(Artifact::EntitySystem& a_EntitySystem, Artifact::MessagingSystem& a_MessagingSystem);

    virtual void registerListeners() override;
private:
    void update(const Artifact::UpdateMessage* a_UpdateMessage);
    void updateTimePassed(const Artifact::UpdateMessage* a_UpdateMessage, TimerComponent* a_Timer);
};


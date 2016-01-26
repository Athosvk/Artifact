#pragma once
#include <BadEngine/Core/System.h>

class TimerComponent;

class TimerSystem : public BadEngine::System
{
public:
    TimerSystem(BadEngine::EntitySystem& a_EntitySystem, BadEngine::MessagingSystem& a_MessagingSystem);

    virtual void registerListeners() override;
private:
    void update(const BadEngine::UpdateMessage* a_UpdateMessage);
    void updateTimePassed(const BadEngine::UpdateMessage* a_UpdateMessage, TimerComponent* a_Timer);
};


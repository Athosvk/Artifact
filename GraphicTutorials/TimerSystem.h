#pragma once
#include <BadEngine/Core/System.h>

class TimerComponent;

class TimerSystem : public BadEngine::System
{
public:
    TimerSystem(BadEngine::EntitySystem& a_EntitySystem, BadEngine::MessagingSystem a_MessagingSystem);

    virtual void registerListeners() override;
private:
    void update();
    void updateTimePassed(TimerComponent* a_Timer);
};


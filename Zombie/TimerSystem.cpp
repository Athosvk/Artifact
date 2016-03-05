#include <Artifact/Core/EntitySystem.h>
#include <Artifact/Core/World.h>

#include "TimerSystem.h" 
#include "TimerComponent.h"

TimerSystem::TimerSystem(Artifact::EntitySystem& a_EntitySystem, Artifact::MessagingSystem& a_MessagingSystem)
    : System(a_EntitySystem, a_MessagingSystem)
{
}

void TimerSystem::registerListeners()
{
    m_MessagingSystem.registerListener<Artifact::UpdateMessage>([this](const Artifact::Message* a_Message)
    {
        update(static_cast<const Artifact::UpdateMessage*>(a_Message));
    });
}

void TimerSystem::update(const Artifact::UpdateMessage* a_UpdateMessage)
{
    for(auto timer : m_EntitySystem.getComponentsOfType<TimerComponent>())
    {
        if(timer->TimerState == ETimerState::Running)
        {
            updateTimePassed(a_UpdateMessage, timer);
        }
    }
}

void TimerSystem::updateTimePassed(const Artifact::UpdateMessage* a_UpdateMessage, TimerComponent* a_TimerComponent)
{
    a_TimerComponent->TimePassed += a_UpdateMessage->getGameTime().getDeltaTime();
    if(a_TimerComponent->TimePassed >= a_TimerComponent->Duration)
    {
        a_TimerComponent->TimerState = ETimerState::Done;
        a_TimerComponent->TimePassed = 0;
    }
}


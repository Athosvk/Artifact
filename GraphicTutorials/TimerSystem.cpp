#include <BadEngine/Core/EntitySystem.h>
#include <BadEngine/Core/World.h>

#include "TimerSystem.h" 
#include "TimerComponent.h"

TimerSystem::TimerSystem(BadEngine::EntitySystem& a_EntitySystem, BadEngine::MessagingSystem& a_MessagingSystem)
    : System(a_EntitySystem, a_MessagingSystem)
{
}

void TimerSystem::registerListeners()
{
    m_MessagingSystem.registerListener<BadEngine::UpdateMessage>([this](const BadEngine::Message* a_Message)
    {
        update(static_cast<const BadEngine::UpdateMessage*>(a_Message));
    });
}

void TimerSystem::update(const BadEngine::UpdateMessage* a_UpdateMessage)
{
    for(auto timer : m_EntitySystem.getComponentsOfType<TimerComponent>())
    {
        if(timer->TimerState == ETimerState::Running)
        {
            updateTimePassed(a_UpdateMessage, timer);
        }
    }
}

void TimerSystem::updateTimePassed(const BadEngine::UpdateMessage* a_UpdateMessage, TimerComponent* a_TimerComponent)
{
    a_TimerComponent->TimePassed += a_UpdateMessage->getGameTime().getDeltaTime();
    if(a_TimerComponent->TimePassed >= a_TimerComponent->Duration)
    {
        a_TimerComponent->TimerState = ETimerState::Done;
        a_TimerComponent->TimePassed = 0;
    }
}


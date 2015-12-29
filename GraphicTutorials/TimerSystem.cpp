#include <BadEngine/Core/EntitySystem.h>

#include "TimerSystem.h" 
#include "TimerComponent.h"

TimerSystem::TimerSystem(BadEngine::EntitySystem& a_EntitySystem)
    : System(a_EntitySystem)
{
}

void TimerSystem::update()
{
    for(auto timer : m_EntitySystem.getComponentsOfType<TimerComponent>())
    {
        if(timer->TimerState == ETimerState::Started)
        {
            updateTimePassed(timer);
        }
    }
}

void TimerSystem::updateTimePassed(TimerComponent* a_TimerComponent)
{
    a_TimerComponent->TimePassed += 0.1f;
    if(a_TimerComponent->TimePassed >= a_TimerComponent->Duration)
    {
        a_TimerComponent->TimerState = ETimerState::Done;
    }
}


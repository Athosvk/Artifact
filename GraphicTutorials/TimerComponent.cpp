#include <BadEngine/Core/GameObject.h>

#include "TimerComponent.h"

TimerComponent::TimerComponent(BadEngine::GameObject a_GameObject)
    : Component(a_GameObject)
{
}

void TimerComponent::start()
{
    TimerState = ETimerState::Running;
}
#include <Artifact/Core/GameObject.h>

#include "TimerComponent.h"

TimerComponent::TimerComponent(Artifact::GameObject a_GameObject)
    : Component(a_GameObject)
{
}

void TimerComponent::start()
{
    TimerState = ETimerState::Running;
    TimePassed = 0.0;
}
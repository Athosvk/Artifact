#pragma once
#include <functional>

#include <BadEngine/Core/Component.h>

enum class ETimerState
{
    Disabled, Started, Done
};

class TimerComponent : BadEngine::Component
{
public:
    ETimerState TimerState = ETimerState::Done;
    float TimePassed = 0.0f;
    float Duration = 0.0f;

public:
    TimerComponent(BadEngine::GameObject a_GameObject);
};


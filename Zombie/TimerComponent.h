#pragma once
#include <functional>

#include <BadEngine/Core/Component.h>

enum class ETimerState
{
    Disabled, Running, Done
};

class TimerComponent : public BadEngine::Component
{
public:
    ETimerState TimerState = ETimerState::Done;
    double TimePassed = 0.0;
    double Duration = 0.0;

public:
    TimerComponent(BadEngine::GameObject a_GameObject);

    void start();
};


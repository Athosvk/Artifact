#pragma once
#include <functional>

#include <Artifact/Core/Component.h>

enum class ETimerState
{
    Disabled, Running, Done
};

class TimerComponent : public Artifact::Component
{
public:
    ETimerState TimerState = ETimerState::Done;
    double TimePassed = 0.0;
    double Duration = 0.0;

public:
    TimerComponent(Artifact::GameObject a_GameObject);

    void start();
};


#pragma once
#include <BadEngine/GameTime.h>
#include <functional>

class Timer
{
private:
    enum class ETimerState
    {
        Disabled, Started, Done
    } m_TimerState = ETimerState::Done;

    std::function<void()> m_CallBack;
    float m_TimePassed = 0.0f;
    float m_Duration = 0.0f;

public:
    Timer(std::function<void()> a_CallBack, float a_Duration);

    void start();
    void update(const BadEngine::GameTime& a_GameTime);
    void reset();
    bool isDone();
};

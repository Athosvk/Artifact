#include "Timer.h"

#include <iostream>

Timer::Timer(std::function<void()> a_CallBack, float a_Duration)
    : m_CallBack(a_CallBack),
    m_Duration(a_Duration)
{
}

void Timer::start()
{
    m_TimerState = ETimerState::Started;
}

void Timer::update(const BadEngine::GameTime& a_GameTime)
{
    if(m_TimerState == ETimerState::Started)
    {
        m_TimePassed += static_cast<float>(a_GameTime.getDeltaTime());
        if(m_TimePassed >= m_Duration)
        {
            if(m_CallBack)
            {
                m_CallBack();
            }
            m_TimerState = ETimerState::Done;
        }
    }
}

void Timer::reset()
{
    m_TimePassed = 0.0f;
    m_TimerState = ETimerState::Disabled;
}

bool Timer::isDone()
{
    return m_TimerState == ETimerState::Done;
}
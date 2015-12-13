#include "Timer.h"

#include <iostream>

Timer::Timer(std::function<void()> a_CallBack, float a_Duration)
    : m_CallBack(a_CallBack),
    m_Duration(a_Duration)
{
}

void Timer::update(const BadEngine::GameTime& a_GameTime)
{
    if(!m_Done)
    {
        m_TimePassed += static_cast<float>(a_GameTime.getDeltaTime());
        if(m_TimePassed >= m_Duration)
        {
            m_CallBack();
            m_Done = true;
        }
    }
}

void Timer::reset()
{
    m_TimePassed = 0.0f;
}

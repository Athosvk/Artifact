#pragma once
#include <BadEngine/GameTime.h>
#include <functional>

class Timer
{
private:
    std::function<void()> m_CallBack;
    float m_TimePassed = 0.0f;
    float m_Duration = 0.0f;
    bool m_Done = false;

public:
    Timer(std::function<void()> a_CallBack, float a_Duration);

    void update(const BadEngine::GameTime& a_GameTime);
    void reset();
};

#include <SDL2.0.3\SDL.h>

#include "GameTime.h"

namespace BadEngine
{
    GameTime::GameTime()
    {
        m_Samples = new double[m_SampleCount];
    }

    GameTime::~GameTime()
    {
        delete[] m_Samples;
    }

    void GameTime::setFrameSampleCount(int a_FrameSampleCount)
    {
        m_SampleCount = a_FrameSampleCount;
        delete[] m_Samples;
        m_Samples = new double[a_FrameSampleCount];
    }

    double GameTime::getCurrentTime() const
    {
        return m_CurrentTime;
    }

    double GameTime::getDeltaTime() const
    {
        return m_DeltaTime;
    }

    double GameTime::getAverageDeltaTime() const
    {
        auto average = 0.0;
        for(auto i = 0; i < m_SampleCount; ++i)
        {
            average += m_Samples[i];
        }
        average /= m_SampleCount;
        return average;
    }

    void GameTime::update()
    {
        m_DeltaTime = m_CurrentTime - m_PreviousTime;
        m_PreviousTime = m_CurrentTime;
        m_CurrentTime = SDL_GetTicks() * 0.001;
        m_Samples[++m_CurrentFrame % m_SampleCount] = m_DeltaTime;
    }
}
#include <SDL\SDL.h>

#include "GameTime.h"

namespace Artifact
{
    GameTime::GameTime()
        : m_Samples(m_SampleCount)
    {
    }

    void GameTime::setFrameSampleCount(int a_FrameSampleCount)
    {
        m_SampleCount = a_FrameSampleCount;
        m_Samples.resize(a_FrameSampleCount);
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
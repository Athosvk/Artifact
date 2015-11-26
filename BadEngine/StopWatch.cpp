#include "StopWatch.h"

namespace BadEngine
{
    StopWatch::StopWatch()
    {
    }

    StopWatch::~StopWatch()
    {
    }

    void StopWatch::start()
    {
        m_Finished = false;
        m_StartTime = std::chrono::high_resolution_clock::now();
    }

    void StopWatch::end()
    {
        m_EndTime = std::chrono::high_resolution_clock::now();
        m_Finished = true;
    }

    double StopWatch::toMilliseconds()
    {
        auto timePassed = (m_Finished ? m_EndTime : std::chrono::high_resolution_clock::now()) - m_StartTime;
        return std::chrono::duration_cast<std::chrono::duration<double>>(timePassed).count();
    }
};

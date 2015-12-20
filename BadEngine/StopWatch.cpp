#include "StopWatch.h"

namespace BadEngine
{
    using namespace std::chrono;

    StopWatch::StopWatch()
    {
    }

    StopWatch StopWatch::startNew()
    {
        StopWatch stopWatch;
        stopWatch.start();
        return stopWatch;
    }

    void StopWatch::start()
    {
        m_Finished = false;
        m_StartTime = high_resolution_clock::now();
    }

    void StopWatch::end()
    {
        m_EndTime = high_resolution_clock::now();
        m_Finished = true;
    }

    long long StopWatch::toNanoseconds()
    {
        auto timePassed = (m_Finished ? m_EndTime : high_resolution_clock::now()) - m_StartTime;
        return duration_cast<nanoseconds>(timePassed).count();
    }
};

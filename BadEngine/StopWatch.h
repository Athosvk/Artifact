#pragma once
#include <chrono>

namespace BadEngine
{
    class StopWatch
    {
    private:
        bool m_Finished;
        std::chrono::high_resolution_clock::time_point m_StartTime;
        std::chrono::high_resolution_clock::time_point m_EndTime;

    public:
        StopWatch();
        ~StopWatch();

        void start();
        void end();
        double toMilliseconds();
    };
};

#pragma once
#include <vector>

namespace BadEngine
{
    class GameTime
    {
    private:
        double m_CurrentTime = 0.0;
        double m_PreviousTime = 0.0;;
        double m_DeltaTime = 0.0;
        int m_CurrentFrame = 1;
        int m_SampleCount = 1;
        double* m_Samples;

    public:
        GameTime();
        ~GameTime();
        double getCurrentTime();
        double getDeltaTime();
        double getAverageDeltaTime();
        void setFrameSampleCount(int a_FrameSampleCount);
        void update();
    };
}


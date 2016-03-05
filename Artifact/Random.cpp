#include "Random.h"

namespace Artifact
{
    std::default_random_engine Random::s_Generator;

    int Random::range(int a_Min, int a_Max)
    {
        std::uniform_int_distribution<int> distribution(a_Min, a_Max);
        return distribution(s_Generator);
    }

    float Random::range(float a_Min, float a_Max)
    {
        std::uniform_real_distribution<float> distribution(a_Min, a_Max);
        return distribution(s_Generator);
    }
}
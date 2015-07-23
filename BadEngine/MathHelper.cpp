#include "MathHelper.h"

namespace BadEngine
{
    float MathHelper::clamp(float a_Value, float a_Min, float a_Max)
    {
        if(a_Value <= a_Min)
        {
            return a_Min;
        }
        if(a_Value >= a_Max)
        {
            return a_Max;
        }
        return a_Value;
    }
}

#pragma once

namespace BadEngine
{
    class MathHelper
    {
    public:
        MathHelper() = delete;
        ~MathHelper() = delete;

        static float clamp(float a_Value, float a_Min, float a_Max);
    };
}

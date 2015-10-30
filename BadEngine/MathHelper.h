#pragma once

namespace BadEngine
{
    class MathHelper
    {
    public:
        MathHelper() = delete;
        ~MathHelper() = delete;
        MathHelper(const MathHelper& a_MatheHelper) = delete;

        static float clamp(float a_Value, float a_Min, float a_Max);
        static float pingPong(float a_Value, float a_Min, float a_Max);
    };
}

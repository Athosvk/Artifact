#pragma once
#include <glm/glm.hpp>

namespace Artifact
{
    class MathHelper
    {
    public:
        MathHelper() = delete;
        ~MathHelper() = delete;

        static float clamp(float a_Value, float a_Min, float a_Max);
        static float pingPong(float a_Value, float a_Min, float a_Max);

        template<typename T>
        static T min(T a_Value1, T a_Value2)
        {
            return a_Value1 < a_Value2 ? a_Value1 : a_Value2;
        }

        template<typename T>
        static T max(T a_Value1, T a_Value2)
        {
            return a_Value1 > a_Value2 ? a_Value1 : a_Value2;
        }

        static glm::vec2 rotate(glm::vec2 a_Vector, float a_Degrees, glm::vec2 a_Origin);
        static glm::vec2 directionFromAngle(float a_Degrees);
        static float directionToAngle(glm::vec2 a_NormalizedDirection);
    };
}

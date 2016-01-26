#pragma once
#include <glm/glm.hpp>

namespace BadEngine
{
    class MathHelper
    {
    public:
        MathHelper() = delete;
        ~MathHelper() = delete;

        static float clamp(float a_Value, float a_Min, float a_Max);
        static float pingPong(float a_Value, float a_Min, float a_Max);
        static glm::vec2 rotate(glm::vec2 a_Vector, float a_Degrees, glm::vec2 a_Origin);
        static glm::vec2 directionFromAngle(float a_Degrees);
        static float directionToAngle(glm::vec2 a_NormalizedDirection);
    };
}

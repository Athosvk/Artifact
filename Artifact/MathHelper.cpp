#include <math.h>
#include <glm/gtc/constants.hpp>

#include "MathHelper.h"

namespace Artifact
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

    glm::vec2 MathHelper::rotate(glm::vec2 a_Vector, float a_Degrees, glm::vec2 a_Origin)
    {
        glm::vec2 rotatedVector;
        auto angleRadians = glm::radians<float>(a_Degrees);
        auto sinAngle = glm::sin(angleRadians);
        auto cosAngle = glm::cos(angleRadians);

        rotatedVector.x = (a_Vector.x - a_Origin.x) * cosAngle - (a_Vector.y - a_Origin.y) * sinAngle + a_Origin.x;
        rotatedVector.y = (a_Vector.x - a_Origin.x) * sinAngle + (a_Vector.y - a_Origin.y) * cosAngle + a_Origin.y;

        return rotatedVector;
    }

    float MathHelper::pingPong(float a_Value, float a_Min, float a_Max)
    {
        auto length = a_Max - a_Min;
        auto wrappedValue = fmod(a_Value, length * 2);
        if(wrappedValue > length)
        {
            wrappedValue = 2 * length - wrappedValue;
        }
        return wrappedValue;
    }

    glm::vec2 MathHelper::directionFromAngle(float a_Degrees)
    {
        return glm::vec2(glm::cos(glm::radians(a_Degrees)), glm::sin(glm::radians(a_Degrees)));
    }

    float MathHelper::directionToAngle(glm::vec2 a_NormalizedDirection)
    {
        return glm::degrees(glm::atan(a_NormalizedDirection.y, a_NormalizedDirection.x));
    }
}

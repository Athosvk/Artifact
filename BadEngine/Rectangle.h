#pragma once
#include <glm/glm.hpp>

namespace BadEngine
{
    class Rectangle
    {
    private:
        glm::vec2 m_MinPosition;
        glm::vec2 m_MaxPosition;

    public:
        Rectangle(const glm::vec2& a_MinPosition, const::glm::vec2& a_MaxPosition);
        Rectangle(const glm::vec2& a_MinPosition, float a_Width, float a_Height);
        ~Rectangle();

        float getWidth() const;
        float getHeight() const;
        float getRadius() const;
        glm::vec2 getCentre() const;
        glm::vec2 getMin() const;
        glm::vec2 getMax() const;
    };
}

#include <iostream>

#include "Rectangle.h"

namespace Artifact
{
    Rectangle::Rectangle(const glm::vec2& a_MinPosition, const glm::vec2& a_MaxPosition)
    {
        if(a_MinPosition.x > a_MaxPosition.x || a_MinPosition.y > a_MaxPosition.y)
        {
            throw std::invalid_argument("Negative width/height");
        }
        m_MinPosition = a_MinPosition;
        m_MaxPosition = a_MaxPosition;
    }

    Rectangle::Rectangle(const glm::vec2& a_MinPosition, float a_Width, float a_Height)
        : m_MinPosition(a_MinPosition),
        m_MaxPosition(glm::vec2(a_MinPosition.x + a_Width, a_MinPosition.y + a_Height))
    {
    }

    Rectangle::Rectangle()
    {
    }

    float Rectangle::getWidth() const
    {
        return m_MaxPosition.x - m_MinPosition.x;
    }

    float Rectangle::getHeight() const
    {
        return m_MaxPosition.y - m_MinPosition.y;
    }

    float Rectangle::getRadius() const
    {
        return glm::length(m_MaxPosition - m_MinPosition) / 2;
    }

    glm::vec2 Rectangle::getPosition() const
    {
        return glm::vec2((m_MinPosition.x + m_MaxPosition.x) / 2,
                         (m_MinPosition.y + m_MaxPosition.y) / 2);
    }

    glm::vec2 Rectangle::getTopLeft() const
    {
        return m_MinPosition;
    }

    glm::vec2 Rectangle::getTopRight() const
    {
        return m_MinPosition + glm::vec2(getWidth(), 0);
    }

    glm::vec2 Rectangle::getBottomLeft() const
    {
        return m_MinPosition + glm::vec2(0, getHeight());
    }

    glm::vec2 Rectangle::getBottomRight() const
    {
        return m_MaxPosition;
    }

    void Rectangle::setWidth(float a_Width)
    {
        m_MaxPosition.x = m_MinPosition.x + a_Width;
    }

    void Rectangle::setHeight(float a_Height)
    {
        m_MaxPosition.y = m_MinPosition.y + a_Height;
    }

    void Rectangle::setMinPosition(glm::vec2 a_MinPosition)
    {
        m_MinPosition = a_MinPosition;
    }

    void Rectangle::setMaxPosition(glm::vec2 a_MaxPosition)
    {
        m_MaxPosition = a_MaxPosition;
    }

    void Rectangle::setPosition(glm::vec2 a_Position)
    {
        glm::vec2 dimensions(getWidth(), getHeight());

        m_MinPosition = a_Position - (dimensions * 0.5f);
        m_MaxPosition = a_Position + (dimensions * 0.5f);
    }
}
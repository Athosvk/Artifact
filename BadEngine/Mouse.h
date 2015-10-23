#pragma once
#include <glm/glm.hpp>

enum class MouseButton
{
    Right,
    Left,
    Middle
};

class Mouse
{
public:
    Mouse();

    glm::vec2 getPosition();
    void setPosition(glm::vec2 a_Position);
    void simulatePress();
};


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
    static glm::vec2 getPosition();
    static void setPosition(glm::vec2 a_Position);
    static void simulatePress();
};


#pragma once
#include <glm/glm.hpp>
#include <SDL2.0.3/SDL.h>

enum class MouseButton
{
    Right,
    Left,
    Middle
};

class Mouse
{
private:
    glm::vec2 m_Position;
    glm::vec2 m_PreviousPosition;

public:
    Mouse();
    ~Mouse();

    glm::vec2 getPosition() const;
    void setPosition(glm::vec2 a_Position);
    void simulatePress();
    void process(SDL_MouseButtonEvent a_ButtonEvent);
    void process(SDL_MouseMotionEvent a_MotionEvent);
    void process(SDL_MouseWheelEvent a_ScrollEvent);
    void update();
};


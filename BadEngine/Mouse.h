#pragma once
#include <glm/glm.hpp>
#include <SDL2.0.3/SDL.h>
#include <vector>

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
    SDL_MouseMotionEvent m_CurrentMotion;
    std::vector<SDL_MouseButtonEvent> m_ButtonEvents;
    std::vector<SDL_MouseWheelEvent> m_ScrollEvents;

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

private:
    void updatePosition();
};


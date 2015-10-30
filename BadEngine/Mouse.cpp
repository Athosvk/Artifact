#include "Mouse.h"

Mouse::Mouse()
{
}

Mouse::~Mouse()
{
}

glm::vec2 Mouse::getPosition() const
{
    return glm::vec2(0, 0);
}

void Mouse::setPosition(glm::vec2 a_Position)
{
    
}

void Mouse::process(SDL_MouseButtonEvent a_ButtonEvent)
{
}

void Mouse::process(SDL_MouseMotionEvent a_MotionEvent)
{
}

void Mouse::process(SDL_MouseWheelEvent a_ScrollEvent)
{
}

void Mouse::update()
{
}
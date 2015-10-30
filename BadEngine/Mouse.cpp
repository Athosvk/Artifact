#include "Mouse.h"

Mouse::Mouse()
{
}

Mouse::~Mouse()
{
}

glm::vec2 Mouse::getPosition() const
{
    return m_Position;
}

void Mouse::setPosition(glm::vec2 a_Position)
{
    
}

void Mouse::process(SDL_MouseButtonEvent a_ButtonEvent)
{
}

void Mouse::process(SDL_MouseMotionEvent a_MotionEvent)
{
    m_CurrentMotion = a_MotionEvent;
}

void Mouse::process(SDL_MouseWheelEvent a_ScrollEvent)
{

}

void Mouse::update()
{
    updatePosition();
}

void Mouse::updatePosition()
{ 
    m_Position.x = m_CurrentMotion.x;
    m_Position.y = m_CurrentMotion.y;
}
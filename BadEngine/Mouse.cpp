#include "Mouse.h"

std::array<bool, Mouse::NumberOfButtons> Mouse::s_CurrentlyPressed;
std::array<bool, Mouse::NumberOfButtons> Mouse::s_PreviouslyPressed;

Mouse::Mouse(const BadEngine::Camera2D& a_Camera)
    : m_Camera(a_Camera)
{
}

Mouse::~Mouse()
{
}

glm::vec2 Mouse::getScreenPosition() const
{
    return m_Position;
}

glm::vec2 Mouse::getWorldPosition() const
{
    return m_Camera.screenToWorld(m_Position);
}

void Mouse::setPosition(glm::vec2 a_Position)
{
    
}

void Mouse::process(SDL_MouseButtonEvent a_ButtonEvent)
{
    m_ButtonEvents.push_back(a_ButtonEvent);
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
    updateButtonStates();
}

bool Mouse::isButtonPressed(MouseButton a_MouseButton)
{
    return isButtonDown(a_MouseButton) && !s_PreviouslyPressed[static_cast<int>(a_MouseButton)];
}

bool Mouse::isButtonDown(MouseButton a_MouseButton)
{
    return s_CurrentlyPressed[static_cast<int>(a_MouseButton)];
}

void Mouse::updatePosition()
{ 
    m_Position.x = m_CurrentMotion.x;
    m_Position.y = m_CurrentMotion.y;
}

void Mouse::updateButtonStates()
{
    for(auto i = 0; i < NumberOfButtons; ++i)
    {
        s_PreviouslyPressed[i] = s_CurrentlyPressed[i];
    }

    std::vector<SDL_MouseButtonEvent>::iterator iterator;
    for(iterator = m_ButtonEvents.begin(); iterator != m_ButtonEvents.end(); ++iterator)
    {
        s_CurrentlyPressed[static_cast<int>(iterator->button)] = iterator->type == SDL_MOUSEBUTTONDOWN;
    }
    m_ButtonEvents.clear();
}
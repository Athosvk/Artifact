#include "Mouse.h"

namespace Artifact
{
    std::array<bool, Mouse::ButtonCount> Mouse::s_CurrentlyPressed;
    std::array<bool, Mouse::ButtonCount> Mouse::s_PreviouslyPressed;
    glm::vec2 Mouse::s_Position;
    Camera2D* Mouse::s_CurrentCamera;

    glm::vec2 Mouse::getScreenPosition()
    {
        return s_Position / static_cast<float>(Camera2D::PixelsPerMeter);
    }

    glm::vec2 Mouse::getWorldPosition()
    {
        return s_CurrentCamera->screenToWorld(s_Position);
    }

    void Mouse::process(SDL_MouseButtonEvent a_ButtonEvent)
    {
        m_ButtonEvents.push_back(a_ButtonEvent);
    }

    void Mouse::process(SDL_MouseMotionEvent a_MotionEvent)
    {
        m_CurrentMotion = a_MotionEvent;
    }

    void Mouse::process(SDL_MouseWheelEvent)
    {

    }

    void Mouse::update()
    {
        updatePosition();
        updateButtonStates();
    }

    void Mouse::onCameraChange(Camera2D* a_NewCamera)
    {
        s_CurrentCamera = a_NewCamera;
    }

    bool Mouse::isButtonPressed(EMouseButton a_MouseButton)
    {
        return isButtonDown(a_MouseButton) && !s_PreviouslyPressed[static_cast<int>(a_MouseButton)];
    }

    bool Mouse::isButtonDown(EMouseButton a_MouseButton)
    {
        return s_CurrentlyPressed[static_cast<int>(a_MouseButton)];
    }

    void Mouse::updatePosition()
    {
        s_Position.x = static_cast<float>(m_CurrentMotion.x);
        s_Position.y = static_cast<float>(m_CurrentMotion.y);
    }

    void Mouse::updateButtonStates()
    {
        for(auto i = 0; i < ButtonCount; ++i)
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
}
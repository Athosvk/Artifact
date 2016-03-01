#include "Keyboard.h"

namespace Artifact
{
    bool Keyboard::m_CurrentlyPressed[SDL_NUM_SCANCODES];
    bool Keyboard::m_PreviouslyPressed[SDL_NUM_SCANCODES];

    Keyboard::Keyboard()
    {
        clear();
    }

    Keyboard::~Keyboard()
    {
    }

    void Keyboard::process(const SDL_KeyboardEvent& a_KeyboardEvent)
    {
        m_KeyboardEvents.push_back(a_KeyboardEvent);
    }

    bool Keyboard::isDown(const KeyCode& a_KeyCode)
    {
        return m_CurrentlyPressed[static_cast<int>(a_KeyCode)];
    }

    bool Keyboard::isPressed(const KeyCode& a_KeyCode)
    {
        return isDown(a_KeyCode) && !m_PreviouslyPressed[static_cast<int>(a_KeyCode)];
    }

    bool Keyboard::isReleased(const KeyCode& a_KeyCode)
    {
        return !isDown(a_KeyCode) && m_PreviouslyPressed[static_cast<int>(a_KeyCode)];
    }

    void Keyboard::clear()
    {
        clearPrevious();
        clearCurrent();
    }

    void Keyboard::clearPrevious()
    {
        for(auto i = 0; i < SDL_NUM_SCANCODES; ++i)
        {
            m_PreviouslyPressed[i] = false;
        }
    }

    void Keyboard::clearCurrent()
    {
        for(auto i = 0; i < SDL_NUM_SCANCODES; ++i)
        {
            m_CurrentlyPressed[i] = false;
        }
    }

    void Keyboard::updateKeystate()
    {
        for(auto i = 0; i < SDL_NUM_SCANCODES; ++i)
        {
            m_PreviouslyPressed[i] = m_CurrentlyPressed[i];
        }

        std::vector<SDL_KeyboardEvent>::iterator iterator;
        for(iterator = m_KeyboardEvents.begin(); iterator != m_KeyboardEvents.end(); ++iterator)
        {
            m_CurrentlyPressed[iterator->keysym.scancode] = iterator->type != SDL_KEYUP;
        }
        m_KeyboardEvents.clear();
    }

    void Keyboard::update()
    {
        updateKeystate();
    }
};
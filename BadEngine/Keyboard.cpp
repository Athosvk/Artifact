#include "Keyboard.h"

namespace BadEngine
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
        for(int i = 0; i < SDL_NUM_SCANCODES; ++i)
        {
            m_CurrentlyPressed[i] = false;
            m_PreviouslyPressed[i] = false;
        }
    }

    void Keyboard::update()
    {
        for(int i = 0; i < SDL_NUM_SCANCODES; ++i)
        {
            m_PreviouslyPressed[i] = m_CurrentlyPressed[i];
        }

        std::vector<SDL_KeyboardEvent>::iterator iterator;
        for(iterator = m_KeyboardEvents.begin(); iterator != m_KeyboardEvents.end(); ++iterator)
        {
            m_CurrentlyPressed[iterator->keysym.scancode] = iterator->type != SDL_KEYUP;
        }
    }
};
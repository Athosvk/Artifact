#pragma once
#include <SDL/SDL.h>
#include <vector>

#include "Keycode.h"

namespace Artifact
{
    class Keyboard
    {
    private:
        std::vector<SDL_KeyboardEvent> m_KeyboardEvents;

        static bool m_PreviouslyPressed[SDL_NUM_SCANCODES];
        static bool m_CurrentlyPressed[SDL_NUM_SCANCODES];

    public:
        Keyboard();
        ~Keyboard();

        void process(const SDL_KeyboardEvent& a_KeyboardEvent);
        void update();

        static bool isPressed(const KeyCode& a_KeyCode);
        static bool isDown(const KeyCode& a_KeyCode);
        static bool isReleased(const KeyCode& a_KeyCode);
        static void clear();

    private:
        static void clearPrevious();
        static void clearCurrent();
        void updateKeystate();
    };
}
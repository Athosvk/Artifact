#pragma once
#include "../Core/System.h"
#include "Keyboard.h"
#include "Mouse.h"

namespace Artifact
{
    class HandleInputMessage : public Message
    {

    };

    class InputSystem : public System
    {
    private:
        Keyboard m_Keyboard;
        Mouse m_Mouse;

    public:
        InputSystem(EntitySystem& a_EntitySystem, MessagingSystem& a_MessagingSystem);

        virtual void registerListeners() override;
    private:
        void processEvents(const std::vector<SDL_Event>& a_Events);
        void updateInput();
    };
}
#include "InputSystem.h"
#include "../Core/World.h"
#include "../Rendering/Camera2D.h"

namespace Artifact
{
    InputSystem::InputSystem(EntitySystem& a_EntitySystem, MessagingSystem& a_MessagingSystem)
        : System(a_EntitySystem, a_MessagingSystem)
    {
        auto cameras = m_EntitySystem.getComponentsOfType<Camera2D>();
        if(!cameras.empty())
        {
            m_Mouse.onCameraChange(cameras[0]);
        }
    }

    void InputSystem::registerListeners()
    {
        m_MessagingSystem.registerListener<OnCameraChangedMessage>([this](const Artifact::Message* a_Message)
        {
            m_Mouse.onCameraChange(static_cast<const OnCameraChangedMessage*>(a_Message)->getNewCamera());
        });
        m_MessagingSystem.registerListener<ProcessEventsMessage>([this](const Artifact::Message* a_Message)
        {
            processEvents(static_cast<const ProcessEventsMessage*>(a_Message)->getEvents());
            updateInput();
        });
    }

    void InputSystem::processEvents(const std::vector<SDL_Event>& a_Events)
    {
        for(auto sdlEvent : a_Events)
        {
            switch(sdlEvent.type)
            {
            case SDL_KEYDOWN:
            case SDL_KEYUP:
                m_Keyboard.process(sdlEvent.key);
                break;
            case SDL_MOUSEBUTTONUP:
            case SDL_MOUSEBUTTONDOWN:
                m_Mouse.process(sdlEvent.button);
                break;
            case SDL_MOUSEMOTION:
                m_Mouse.process(sdlEvent.motion);
                break;
            case SDL_MOUSEWHEEL:
                m_Mouse.process(sdlEvent.wheel);
                break;
            }
        }
    }

    void InputSystem::updateInput()
    {
        m_Mouse.update();
        m_Keyboard.update();
        m_MessagingSystem.broadcast<HandleInputMessage>();
    }
}

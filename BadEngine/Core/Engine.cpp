#include "Engine.h"
#include "Message.h"
#include "System.h"

namespace BadEngine
{
    Engine::Engine()
    {
    }

    Engine::~Engine()
    {
    }

    void Engine::update()
    {
        
    }

    void Engine::broadCast(Message* a_MessageType)
    {
        for(auto& system : m_Systems)
        {
            system->sendMessage(a_MessageType);
        }
    }

    void Engine::run()
    {
    }
}
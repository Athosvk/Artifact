#include "World.h"
#include "Message.h"
#include "System.h"

namespace BadEngine
{
    void World::broadCast(const Message* a_MessageType)
    {
        for(auto& system : m_Systems)
        {
            system->sendMessage(a_MessageType);
        }
    }
}
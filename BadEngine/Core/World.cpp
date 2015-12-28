#include "World.h"
#include "Message.h"
#include "System.h"

namespace BadEngine
{
    World::World()
    {
    }

    World::~World()
    {
    }

    void World::update()
    {
        
    }

    void World::broadCast(Message* a_MessageType)
    {
        for(auto& system : m_Systems)
        {
            system->sendMessage(a_MessageType);
        }
    }

    void World::run()
    {
    }
}
#include "EntitySystem.h"
#include "GameObject.h"

namespace BadEngine
{   
    EntitySystem::EntitySystem(MessagingSystem& a_MessagingSystem)
        : m_MessagingSystem(a_MessagingSystem)
    {
    }

    unsigned EntitySystem::generateNextID()
    {
        return m_LastID++;
    }
}
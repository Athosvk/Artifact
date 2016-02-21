#include "EntitySystem.h"
#include "GameObject.h"

namespace BadEngine
{   
    EntitySystem::EntitySystem(MessagingSystem& a_MessagingSystem)
        : m_MessagingSystem(a_MessagingSystem)
    {
    }

    bool EntitySystem::isActive(unsigned a_EntityID)
    {
        return m_EntityStates[a_EntityID].Active;
    }

    void EntitySystem::activate(unsigned a_EntityID)
    {
        m_EntityStates[a_EntityID].Active = true;
    }

    void EntitySystem::deactivate(unsigned a_EnittyID)
    {
        m_EntityStates[a_EnittyID].Active = false;
    }

    unsigned EntitySystem::generateNextID()
    {
        return m_LastID++;
    }
}
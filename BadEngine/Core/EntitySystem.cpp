#include "EntitySystem.h"
#include "GameObject.h"
#include "Component.h"

namespace BadEngine
{
    EntitySystem::EntitySystem()
    {
    }

    EntitySystem::~EntitySystem()
    {
    }

    unsigned EntitySystem::generateNextID()
    {
        return m_LastID++;
    }
}
#include "EntitySystem.h"
#include "GameObject.h"

namespace BadEngine
{
    GameObject EntitySystem::createEntity()
    {
        return GameObject(generateNextID(), *(this));
    }

    unsigned EntitySystem::generateNextID()
    {
        return m_LastID++;
    }
}
#include "EntitySystem.h"
#include "GameObject.h"
#include "Component.h"

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
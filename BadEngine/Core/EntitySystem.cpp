#include "EntitySystem.h"
#include "GameObject.h"
#include "Component.h"

namespace BadEngine
{
    unsigned EntitySystem::generateNextID()
    {
        return m_LastID++;
    }
}
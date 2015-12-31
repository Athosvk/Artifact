#include "EntitySystem.h"
#include "GameObject.h"

namespace BadEngine
{   
    unsigned EntitySystem::generateNextID()
    {
        return m_LastID++;
    }
}
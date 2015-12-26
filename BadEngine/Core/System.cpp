#include "System.h"
#include "EntitySystem.h"

namespace BadEngine
{
    System::System(EntitySystem& a_EntitySystem)
        : m_EntitySystem(a_EntitySystem)
    {
    }
}
#pragma once
#include <vector>

#include "MessagingSystem.h"

namespace Artifact
{
    class EntitySystem;

    class System
    {
    protected:
        EntitySystem& m_EntitySystem;
        MessagingSystem& m_MessagingSystem;

    public:
        System(EntitySystem& a_EntitySystem, MessagingSystem& a_MessagingSystem);
        virtual ~System() = default;

        virtual void registerListeners() = 0;
    };
}
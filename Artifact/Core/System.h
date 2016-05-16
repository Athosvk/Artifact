#pragma once
#include <vector>

namespace Artifact
{
    class EntitySystem;
	class MessagingSystem;

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
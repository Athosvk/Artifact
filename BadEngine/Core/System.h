#pragma once
#include <vector>

#include "Message.h"

namespace BadEngine
{
    class EntitySystem;

    class System
    {
    protected:
        EntitySystem& m_EntitySystem;

    public:
        System(EntitySystem& a_EntitySystem);

        virtual void sendMessage(const Message* a_Message) = 0;
    };
}
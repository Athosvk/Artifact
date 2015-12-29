#pragma once
#include <memory>
#include <vector>
#include <utility>

#include "EntitySystem.h"
#include "MessagingSystem.h"

namespace BadEngine
{
    class System;
    class Message;

    class World
    {
    private:
        std::vector<std::unique_ptr<System>> m_Systems;
        EntitySystem m_EntitySystem;
        MessagingSystem m_MessagingSystem;

    public:
        World();

        void update();
        void fixedUpdate();

        template<typename T>
        void addSystem()
        {
            m_Systems.push_back(std::make_unique<T>(m_EntitySystem));
        }

        template<typename TMessageType, typename... TArguments>
        void broadcast(TArguments&&... a_MessageArguments)
        {
            m_MessagingSystem.broadcast<TMessageType, TArguments...>(m_Systems, std::forward<TArguments>(a_MessageArguments)...);
        }
    };
}


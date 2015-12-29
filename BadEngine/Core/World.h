#pragma once
#include <memory>
#include <vector>

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
        void update();

        template<typename T>
        void addSystem()
        {
            m_Systems.push_back(std::make_unique<T>(m_EntitySystem));
        }

        void broadCast(const Message* a_Message);
    };
}


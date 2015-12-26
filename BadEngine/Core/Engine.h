#pragma once
#include <memory>
#include <vector>

#include "EntitySystem.h"

namespace BadEngine
{
    class System;
    class Message;

    class Engine
    {
    private:
        std::vector<std::unique_ptr<System>> m_Systems;
        EntitySystem m_EntitySystem;

    public:
        Engine();
        ~Engine();
    
        void run();

    private:
        void update();
        void broadCast(Message* a_Message);
    };
}


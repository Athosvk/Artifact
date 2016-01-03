#pragma once
#include <memory>
#include <vector>
#include <utility>

#include "EntitySystem.h"
#include "MessagingSystem.h"
#include "../Rendering/Camera2D.h"
#include "System.h"
#include "../GameTime.h"

namespace BadEngine
{
    class System;
    class Message;
    class GameTime;
    
    class UpdateMessage : public Message
    {
        const GameTime& m_GameTime;
        
    public:
        UpdateMessage(const GameTime& a_GameTime);

        const GameTime& getGameTime();
    };

    class FixedUpdateMessage : public Message
    {
    };

    class HandleInputMessage : public Message
    {
    };

    class World
    {
    protected:
        EntitySystem m_EntitySystem;
        MessagingSystem m_MessagingSystem;

    private:
        std::vector<std::unique_ptr<System>> m_Systems;
        Camera2D m_Camera;
        GameTime m_GameTime;

    public:
        World(const Window& a_Window);

        void* operator new(std::size_t a_Size);

        void operator delete(void* a_Pointer);

        void update();
        void fixedUpdate();

        template<typename TMessageType, typename... TArguments>
        void broadcast(TArguments&&... a_MessageArguments)
        {
            m_MessagingSystem.broadcast<TMessageType, TArguments...>(std::forward<TArguments>(a_MessageArguments)...);
        }

    protected:
        template<typename T>
        void addSystem()
        {
            auto newSystem = std::make_unique<T>(m_EntitySystem, m_MessagingSystem);
            newSystem->registerListeners();
            m_Systems.emplace_back(std::move(newSystem));
        }

    private:
        void addDefaultSystems();
    };
}


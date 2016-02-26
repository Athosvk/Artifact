#pragma once
#include <memory>
#include <vector>
#include <utility>
#include <SDL2.0.3/SDL.h>

#include "EntitySystem.h"
#include "MessagingSystem.h"
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

        const GameTime& getGameTime() const;
    };

    class FixedUpdateMessage : public Message
    {
    };

    class ProcessEventsMessage : public Message
    {
        const std::vector<SDL_Event>& m_Events;

    public:
        ProcessEventsMessage(const std::vector<SDL_Event>& a_Events);

        const std::vector<SDL_Event>& getEvents() const;
    };

    class PhysicsUpdateMessage : public Message
    {
    };

    class World
    {
    protected:
        EntitySystem m_EntitySystem;
        MessagingSystem m_MessagingSystem;

    private:
        std::vector<std::unique_ptr<System>> m_Systems;
        GameTime& m_GameTime;

    public:
        World(GameTime& a_GameTime);

        void update();
        void fixedUpdate();
        void processEvents(std::vector<SDL_Event>& a_Events);
    protected:
        template<typename T>
        void addSystem()
        {
            auto newSystem = std::make_unique<T>(m_EntitySystem, m_MessagingSystem);
            newSystem->registerListeners();
            m_Systems.emplace_back(std::move(newSystem));
        }

        template<typename TMessageType, typename... TArguments>
        void broadcast(TArguments&&... a_MessageArguments)
        {
            m_MessagingSystem.broadcast<TMessageType, TArguments...>(std::forward<TArguments>(a_MessageArguments)...);
        }

    private:
        void addDefaultSystems();
    };
}


#pragma once
#include <memory>

#include "System.h"

namespace BadEngine
{
    class Message;

    class MessagingSystem
    {
    public:
        template<typename TMessageType, typename... TArguments>
        void broadcast(std::vector<std::unique_ptr<System>>& a_Systems, TArguments&&... a_MessageArguments)
        {
            std::unique_ptr<TMessageType> newMessage = std::make_unique<TMessageType>(std::forward<TArguments>(a_MessageArguments)...);
            for(auto& system : a_Systems)
            {
                system->sendMessage(newMessage.get());
            }
        }
    };
}

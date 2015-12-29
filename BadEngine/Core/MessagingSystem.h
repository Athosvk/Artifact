#pragma once
#include <memory>

#include "System.h"

namespace BadEngine
{
    class Message;

    class MessagingSystem
    {
    public:
        template<typename T>
        void broadcast(T a_Message, std::vector<std::unique_ptr<System>>& a_Systems)
        {
            std::unique_ptr<Message> newMessage = std::make_unique<T>(a_Message);
            for(auto& system : a_Systems)
            {
                system->sendMessage(newMessage.get());
            }
        }
    };
}

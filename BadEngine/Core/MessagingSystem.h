#pragma once
#include <memory>
#include <unordered_map>
#include <functional>

#include "System.h"

namespace BadEngine
{
    class MessagingSystem
    {
    private:
        std::unordered_map<std::type_index, std::vector<std::function<void(Message* a_Message)>>> m_MessageListeners;

    public:
        template<typename TMessageType, typename... TArguments>
        void broadcast(TArguments&&... a_MessageArguments) const
        {
            std::unique_ptr<Message> newMessage = std::make_unique<TMessageType>(std::forward<TArguments>(a_MessageArguments)...);
            for(auto& listener : m_MessageListeners[typeid(TMessageType)])
            {
                listener(newMessage.get());
            }
        }

        template<typename TMessageType>
        void registerListener(std::function<void(Message* a_Message)> a_Callback)
        {
            m_MessageListeners[typeid(TMessageType)].push_back(a_Callback);
        }
    };
}

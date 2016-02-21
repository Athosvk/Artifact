#pragma once
#include <memory>
#include <unordered_map>
#include <map>
#include <functional>
#include <typeindex>

#include "../Delegate.h"
#include "GameObject.h"

namespace BadEngine
{
    class Message
    {
    };

    class MessagingSystem
    {
    private:
        std::unordered_map<std::type_index, Delegate<void(const Message*)>> m_MessageListeners;
        std::unordered_map<std::type_index, std::map<unsigned, Delegate<void(const Message*)>>> m_ObjectMessageListeners;

    public:
        template<typename TMessageType, typename... TArguments>
        void broadcast(TArguments&&... a_MessageArguments)
        {
            auto newMessage = TMessageType(std::forward<TArguments>(a_MessageArguments)...);

            auto iterator = m_MessageListeners.find(typeid(TMessageType));
            if(iterator != m_MessageListeners.end())
            {
                iterator->second(&newMessage);
            }
        }

        template<typename TMessageType, typename... TArguments>
        void sendMessage(GameObject a_GameObject, TArguments&&... a_MessageArguments)
        {
            auto newMessage = TMessageType(std::forward<TArguments>(a_MessageArguments)...);

            auto typeIterator = m_ObjectMessageListeners.find(typeid(TMessageType));
            if(typeIterator != m_ObjectMessageListeners.end())
            {  
                auto listenerIterator = typeIterator->second.find(a_GameObject.getID());
                if(listenerIterator != typeIterator->second.end())
                {
                    listenerIterator->second(&newMessage);
                }
            }
        }

        template<typename TMessageType>
        void registerListener(std::function<void(const Message* a_Message)> a_Callback)
        {
            m_MessageListeners[typeid(TMessageType)] += a_Callback;
        }

        template<typename TMessageType>
        void registerListener(std::function<void(const Message* a_Message)> a_Callback, GameObject a_GameObject)
        {
            m_ObjectMessageListeners[typeid(TMessageType)][a_GameObject.getID()] += a_Callback;
        }
    };
}

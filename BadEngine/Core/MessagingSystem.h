#pragma once
#include <memory>
#include <unordered_map>
#include <functional>
#include <typeindex>

namespace BadEngine
{
    class Message
    {
    };

    class MessagingSystem
    {
    private:
        std::unordered_map<std::type_index, std::vector<std::function<void(const Message*)>>> m_MessageListeners;

    public:
        template<typename TMessageType, typename... TArguments>
        void broadcast(TArguments&&... a_MessageArguments)
        {
            auto newMessage = TMessageType(std::forward<TArguments>(a_MessageArguments)...);

            auto iterator = m_MessageListeners.find(typeid(TMessageType));
            if(iterator != m_MessageListeners.end())
            {
                for(auto& listener : iterator->second)
                {
                    listener(&newMessage);
                }
            }
        }

        template<typename TMessageType>
        void registerListener(std::function<void(const Message* a_Message)> a_Callback)
        {
            m_MessageListeners[typeid(TMessageType)].push_back(a_Callback);
        }
    };
}

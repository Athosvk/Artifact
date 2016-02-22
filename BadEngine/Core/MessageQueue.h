#pragma once
#include <vector>
#include <memory>
#include <typeindex>

#include "MessagingSystem.h"

namespace BadEngine
{
    class MessageQueue
    {
    private:
        struct QueuedMessage
        {
        private:
            std::unique_ptr<Message> m_Message;
            std::type_index m_MessageType;

        public:
            QueuedMessage(std::unique_ptr<Message>&& a_Message, std::type_index a_Type);

            Message* getMessage() const;
            std::type_index getMessageType() const;
        };

        std::vector<QueuedMessage> m_Messages;

    public:
        MessageQueue();

        template<typename TMessageType, typename ...TArguments>
        void enqueue(TArguments&&... a_MessageArguments)
        {
            m_Messages.emplace(std::make_unique<TMessageType>(std::forward<TArguments>(a_MessageArguments)...),
                typeid(TMessageType));
        }
    };
}

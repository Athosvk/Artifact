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
            GameObject m_Target;

        public:
            QueuedMessage(std::unique_ptr<Message>&& a_Message, std::type_index a_Type, GameObject a_Target);

            const Message* getMessage() const;
            std::type_index getMessageType() const;
            GameObject getTarget() const;
        };

        std::vector<QueuedMessage> m_Messages;
        std::vector<int> m_Stuff;

    public:
        MessageQueue();

        auto begin()->decltype(m_Messages.begin());
        auto end()->decltype(m_Messages.end());

        template<typename TMessageType, typename ...TArguments>
        void enqueue(GameObject a_Target, TArguments&&... a_MessageArguments)
        {
            m_Messages.emplace(std::make_unique(std::forward<TArguments>(a_MessageArguments)...),
                typeid(TMessageType), a_Target);
        }
    };
}

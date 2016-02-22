#include "MessageQueue.h"

namespace BadEngine
{
    MessageQueue::QueuedMessage::QueuedMessage(std::unique_ptr<BadEngine::Message>&& a_Message, std::type_index a_Type)
        : m_Message(std::move(a_Message)),
        m_MessageType(a_Type)
    {
    }

    Message* MessageQueue::QueuedMessage::getMessage() const
    {
        return m_Message.get();
    }

    std::type_index MessageQueue::QueuedMessage::getMessageType() const
    {
        return m_MessageType;
    }

    MessageQueue::MessageQueue()
    {
    }
}

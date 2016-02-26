#include "MessageQueue.h"

namespace BadEngine
{
    MessageQueue::QueuedMessage::QueuedMessage(std::unique_ptr<BadEngine::Message>&& a_Message, 
        std::type_index a_Type, GameObject a_Target)
        : m_Message(std::move(a_Message)),
        m_MessageType(a_Type),
        m_Target(a_Target)
    {
    }

    const Message* MessageQueue::QueuedMessage::getMessage() const
    {
        return m_Message.get();
    }

    std::type_index MessageQueue::QueuedMessage::getMessageType() const
    {
        return m_MessageType;
    }

    GameObject MessageQueue::QueuedMessage::getTarget() const
    {
        return m_Target;
    }

    MessageQueue::MessageQueue()
    {
    }

    //No trailing return type; the compiler will spit out errors if done so
    std::vector<MessageQueue::QueuedMessage>::iterator MessageQueue::begin()
    {
        return m_Messages.begin();
    }

    //No trailing return type; the compile will spit out errors if done so
    std::vector<MessageQueue::QueuedMessage>::iterator MessageQueue::end()
    {
        return m_Messages.end();
    }
}

#include "Message.h"

namespace BadEngine
{
    Message::Message(EMessageType a_MessageType)
        : m_Type(a_MessageType)
    {
    }

    EMessageType Message::getType() const
    {
        return m_Type;
    }
}
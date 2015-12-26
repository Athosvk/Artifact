#include "Message.h"

namespace BadEngine
{
    Message::Message()
    {

    }

    EMessageType Message::getType() const
    {
        return m_Type;
    }
}
#include "Message.h"

namespace BadEngine
{
    UpdateMessage::UpdateMessage(const GameTime& a_GameTime)
        : m_GameTime(a_GameTime)
    {
    }

    const GameTime& UpdateMessage::getGameTime()
    {
        return m_GameTime;
    }
}
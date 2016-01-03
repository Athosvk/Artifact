#pragma once
#include "../GameTime.h"

namespace BadEngine
{
    class Message
    {
    };

    class UpdateMessage : Message
    {
        const GameTime& m_GameTime;

        UpdateMessage(const GameTime& a_GameTime);

        const GameTime& getGameTime();
    };

    class FixedUpdatemessage : Message
    {
    };

    class HandleInputMessage : Message
    {
    };
}

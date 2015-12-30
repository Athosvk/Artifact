#include "RenderMessage.h"

namespace BadEngine
{
    RenderMessage::RenderMessage(const glm::mat4* a_ViewMatrix)
        : Message(EMessageType::Render),
        m_ViewMatrix(a_ViewMatrix)
    {
    }

    const glm::mat4* RenderMessage::getViewMatrix() const
    {
        return m_ViewMatrix;
    }
}
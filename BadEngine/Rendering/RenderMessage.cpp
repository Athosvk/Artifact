#include "RenderMessage.h"

namespace BadEngine
{
    RenderMessage::RenderMessage(const glm::mat4* a_ViewMatrix) 
        : m_ViewMatrix(a_ViewMatrix)
    {
    }

    const glm::mat4* RenderMessage::getViewMatrix() const
    {
        return m_ViewMatrix;
    }
}
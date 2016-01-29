#pragma once
#include <glm/glm.hpp>

#include "../Core/MessagingSystem.h"

namespace BadEngine
{
    class RenderMessage : public Message
    {
    private:
        const glm::mat4* m_ViewMatrix;

    public:
        RenderMessage(const glm::mat4* a_ViewMatrix);

        const glm::mat4* getViewMatrix() const;
    };
}

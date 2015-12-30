#pragma once
#include <glm/glm.hpp>

#include "../Core/Component.h"

namespace BadEngine
{
    class MovementComponent : public BadEngine::Component
    {
    public:
        glm::vec2 Direction = glm::vec2(0.0f, 0.0f);
        float Speed;

    public:
        MovementComponent(BadEngine::GameObject a_GameObject);
    };
}
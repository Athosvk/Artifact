#pragma once
#include <glm/glm.hpp>

#include "../Core/Component.h"

namespace BadEngine
{
    class RigidBody : public Component
    {
    public:
        glm::vec2 Velocity;

    public:
        RigidBody(GameObject a_GameObject);
    };
}

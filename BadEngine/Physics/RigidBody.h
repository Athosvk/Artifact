#pragma once
#include <Box2D/Box2D.h>
#include <glm/glm.hpp>

#include "../Core/Component.h"

namespace BadEngine
{
    class BoxCollider2D;

    class RigidBody : public Component
    {
        friend class PhysicsWorld;
        friend class PhysicsSystem;
    private:
        b2Body* m_Body = nullptr;

    public:
        RigidBody(GameObject a_GameObject);
        ~RigidBody();

        glm::vec2 getVelocity() const;
        void setVelocity(glm::vec2 a_Velocity);
    private:
        void updateState();
    };
}

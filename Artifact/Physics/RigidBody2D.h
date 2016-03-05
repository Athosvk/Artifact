#pragma once
#include <Box2D/Box2D.h>
#include <glm/glm.hpp>

#include "../Core/Component.h"

namespace Artifact
{
    class BoxCollider2D;

    class RigidBody2D : public Component
    {
        friend class PhysicsWorld;
        friend class PhysicsSystem;
    private:
        b2Body* m_Body = nullptr;

    public:
        RigidBody2D(GameObject a_GameObject);

        glm::vec2 getVelocity() const;
        void setVelocity(glm::vec2 a_Velocity);
        void setGravityScale(float a_Scale);
        void makeKinematic();
        void makeDynamic();
        bool isKinematic() const;
    private:
        void updateState();
    };
}

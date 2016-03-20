#pragma once
#include <Box2D/Box2D.h>

#include "../Core/System.h"
#include "PhysicsWorld.h"

namespace Artifact
{
    class BoxCollider2D;
    class RigidBody2D;

    class PhysicsSystem : public System
    {
    private:
        PhysicsWorld m_PhysicsWorld;

    public:
        PhysicsSystem(EntitySystem& a_EntitySystem, MessagingSystem& a_MessagingSystem);

        void registerListeners();
    private:
        void onRigidBodyAdd(RigidBody2D* a_RigidBody);
        void onColliderAdd(BoxCollider2D* a_Collider);
        void registerActiveMessages(GameObject a_Entity);
        void updatePhysics();
        void postPhysicsUpdate();
        void updateTransforms();
    };
}

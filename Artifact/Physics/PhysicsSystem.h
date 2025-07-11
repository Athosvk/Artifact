#pragma once
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

	    virtual void registerListeners() override;
    private:
        void onRigidBodyAdd(ComponentHandle<RigidBody2D> a_RigidBody);
        void onColliderAdd(ComponentHandle<BoxCollider2D> a_Collider);
        void registerActiveMessages(GameObject a_Entity) const;
        void updatePhysics();
        void postPhysicsUpdate();
        void updateTransforms() const;
    };
}

#pragma once
#include <Box2D/Box2D.h>
#include <memory>
#include <map>

#include "../Core/System.h"
#include "PhysicsWorld.h"

namespace BadEngine
{
    class BoxCollider2D;
    class RigidBody;

    class PhysicsSystem : public System
    {
    private:
        PhysicsWorld m_PhysicsWorld;
        std::map<unsigned, RigidBody*> m_Uninitialised;

    public:
        PhysicsSystem(EntitySystem& a_EntitySystem, MessagingSystem& a_MessagingSystem);

        void registerListeners();
    private:
        void onRigidBodyAdd(RigidBody* a_RigidBody);
        void onColliderAdd(BoxCollider2D* a_Collider);
        void fixedUpdate();
        void updateTransforms();
    };
}

#pragma once
#include <Box2D/Box2D.h>
#include <memory>
#include <map>

#include "../Core/System.h"

namespace BadEngine
{
    class BoxCollider2D;
    class RigidBody;

    class PhysicsSystem : public System
    {
    private:
        static const b2Vec2 Gravity;
        static const int VelocityIterations;
        static const int PositionIterations;

        std::unique_ptr<b2World> m_PhysicsWorld = std::make_unique<b2World>(Gravity);
        std::map<unsigned, std::pair<BoxCollider2D*, RigidBody*>> m_UninitialisedColliders;

    public:
        PhysicsSystem(EntitySystem& a_EntitySystem, MessagingSystem& a_MessagingSystem);

        void registerListeners();
    private:
        void fixedUpdate();
        void initialiseColliders();
        void updateTransforms();
        void createBody(BoxCollider2D* a_Collider, RigidBody* a_RigidBody);
        void createFixture(BoxCollider2D* a_Collider, RigidBody* a_RigidBody);
    };
}

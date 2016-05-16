#pragma once
#include <Box2D\Box2D.h>

#include "CollisionListener.h"

namespace Artifact
{
    class RigidBody2D;
    class BoxCollider2D;

    class PhysicsWorld
    {
    private:
        static const b2Vec2 Gravity;
        static const int VelocityIterations;
        static const int PositionIterations;

        b2World m_World = b2World(Gravity);
        CollisionListener m_CollisionListener;

    public:
        PhysicsWorld(MessagingSystem& a_MessagingSystem);

        void emplace(ComponentHandle<BoxCollider2D> a_Collider);
        void emplace(ComponentHandle<RigidBody2D> a_RigidBody);
        void fixedUpdate();
        void postPhysicsUpdate();
    private:
        b2Body* createBody(ComponentHandle<Transform> a_Transform, b2BodyType a_BodyType);
    };
}


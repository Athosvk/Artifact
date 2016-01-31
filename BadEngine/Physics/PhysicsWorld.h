#pragma once
#include <Box2D\Box2D.h>

#include "CollisionListener.h"

namespace BadEngine
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
        PhysicsWorld(CollisionListener a_CollisionListener);

        void emplace(BoxCollider2D* a_Collider, RigidBody2D* a_RigidBody);
        void fixedUpdate();
    private:
        void createBody(BoxCollider2D* a_Collider, RigidBody2D* a_RigidBody);
    };
}


#pragma once
#include <Box2D\Box2D.h>

namespace BadEngine
{
    class RigidBody;
    class BoxCollider2D;

    class PhysicsWorld
    {
    private:
        static const b2Vec2 Gravity;
        static const int VelocityIterations;
        static const int PositionIterations;

        b2World m_World = b2World(Gravity);

    public:
        PhysicsWorld();

        void emplace(BoxCollider2D* a_Collider, RigidBody* a_RigidBody);
        void fixedUpdate();
    private:
        void createBody(BoxCollider2D* a_Collider, RigidBody* a_RigidBody);
    };
}


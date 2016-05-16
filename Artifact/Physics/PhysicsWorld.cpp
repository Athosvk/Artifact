#include "PhysicsWorld.h"
#include "BoxCollider2D.h"
#include "RigidBody2D.h"
#include "../Game.h"
#include "../Transform.h"

namespace Artifact
{
    const b2Vec2 PhysicsWorld::Gravity = b2Vec2(0, 9.81f);
    const int PhysicsWorld::VelocityIterations = 6;
    const int PhysicsWorld::PositionIterations = 2;

    PhysicsWorld::PhysicsWorld(MessagingSystem& a_MessagingSystem)
        : m_CollisionListener(a_MessagingSystem)
    {
        m_World.SetContactListener(&m_CollisionListener);
    }

    void PhysicsWorld::fixedUpdate()
    {
        m_World.Step(static_cast<float>(Game::FixedUpdateInterval), VelocityIterations, PositionIterations);
    }

    void PhysicsWorld::postPhysicsUpdate()
    {
        m_CollisionListener.postStep();
    }

    void PhysicsWorld::emplace(ComponentHandle<BoxCollider2D> a_Collider)
    {
        a_Collider->m_Body = createBody(a_Collider->getComponent<Transform>(), b2BodyType::b2_staticBody);
    }

    void PhysicsWorld::emplace(ComponentHandle<RigidBody2D> a_RigidBody)
    {
        a_RigidBody->m_Body = createBody(a_RigidBody->getComponent<Transform>(), b2BodyType::b2_dynamicBody);
    }

    b2Body* PhysicsWorld::createBody(ComponentHandle<Transform> a_Transform, b2BodyType a_BodyType)
    {
        b2BodyDef bodyDefinition;
        bodyDefinition.position.Set(a_Transform->getPosition().x, a_Transform->getPosition().y);
        bodyDefinition.angle = a_Transform->getRotation();
        bodyDefinition.type = a_BodyType;

        return m_World.CreateBody(&bodyDefinition);
    }
}
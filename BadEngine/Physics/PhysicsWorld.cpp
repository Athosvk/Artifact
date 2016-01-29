#include "PhysicsWorld.h"
#include "BoxCollider2D.h"
#include "RigidBody.h"
#include "../Game.h"
#include "../Transform.h"

namespace BadEngine
{
    const b2Vec2 PhysicsWorld::Gravity = b2Vec2(0, -90.81f);
    const int PhysicsWorld::VelocityIterations = 6;
    const int PhysicsWorld::PositionIterations = 2;

    PhysicsWorld::PhysicsWorld()
    {
    }

    void PhysicsWorld::fixedUpdate()
    {
        m_World.Step(static_cast<float>(Game::FixedUpdateInterval), VelocityIterations, PositionIterations);
    }

    void PhysicsWorld::emplace(BoxCollider2D* a_Collider, RigidBody* a_RigidBody)
    {
        createBody(a_Collider, a_RigidBody);
    }

    void PhysicsWorld::createBody(BoxCollider2D* a_Collider, RigidBody* a_RigidBody)
    {
        b2BodyDef bodyDefinition;
        auto transform = a_Collider->getComponent<Transform>();
        bodyDefinition.position.Set(transform->getPosition().x, transform->getPosition().y);
        bodyDefinition.angle = transform->getRotation();
        bodyDefinition.type = a_RigidBody != nullptr ? b2BodyType::b2_dynamicBody : b2BodyType::b2_staticBody;

        auto body = m_World.CreateBody(&bodyDefinition);
        a_Collider->m_Body = body;
        if(a_RigidBody != nullptr)
        {
            a_RigidBody->m_Body = body;
        }
    }
}
#include "PhysicsSystem.h"
#include "BoxCollider2D.h"
#include "RigidBody.h"
#include "../Core/EntitySystem.h"
#include "../Core/World.h"
#include "../Transform.h"
#include "../Game.h"


namespace BadEngine
{
    const b2Vec2 PhysicsSystem::Gravity = b2Vec2(0, -90.81f);
    const int PhysicsSystem::VelocityIterations = 6;
    const int PhysicsSystem::PositionIterations = 2;

    PhysicsSystem::PhysicsSystem(EntitySystem& a_EntitySystem, MessagingSystem& a_MessagingSystem)
        : System(a_EntitySystem, a_MessagingSystem)
    {
    }

    void PhysicsSystem::registerListeners()
    {
        m_MessagingSystem.registerListener<ComponentAddedMessage<BoxCollider2D>>([this](const Message* a_Message)
        {
            auto collider = static_cast<const ComponentAddedMessage<BoxCollider2D>*>(a_Message)->getAddedComponent();
            m_UninitialisedColliders[collider->getGameObject().getID()].first = collider;
        });
        m_MessagingSystem.registerListener<ComponentAddedMessage<RigidBody>>([this](const Message* a_Message)
        {
            auto rigidBody = static_cast<const ComponentAddedMessage<RigidBody>*>(a_Message)->getAddedComponent();
            m_UninitialisedColliders[rigidBody->getGameObject().getID()].second = rigidBody;
        });
        m_MessagingSystem.registerListener<FixedUpdateMessage>([this](const Message* a_Message)
        {
            fixedUpdate();
        });
    }

    void PhysicsSystem::fixedUpdate()
    {
        initialiseColliders();
        m_PhysicsWorld->Step(static_cast<float>(Game::FixedUpdateInterval), VelocityIterations, PositionIterations);
        for(auto rigidBody : m_EntitySystem.getComponentsOfType<RigidBody>())
        {
            rigidBody->updateState();
        }
    }

    void PhysicsSystem::initialiseColliders()
    {
        for(auto& colliderPair : m_UninitialisedColliders)
        {
            createBody(colliderPair.second.first, colliderPair.second.second);
            createFixture(colliderPair.second.first, colliderPair.second.second);
        }
        m_UninitialisedColliders.clear();
    }

    void PhysicsSystem::createBody(BoxCollider2D* a_Collider, RigidBody* a_RigidBody)
    {
        b2BodyDef bodyDefinition;
        auto transform = a_Collider->getComponent<Transform>();
        bodyDefinition.position.Set(transform->getPosition().x, transform->getPosition().y);
        bodyDefinition.angle = transform->getRotation();

        bodyDefinition.type = a_RigidBody != nullptr ? b2BodyType::b2_dynamicBody : b2_staticBody;

        auto body = m_PhysicsWorld->CreateBody(&bodyDefinition);
        
        a_Collider->m_Body = body;
        if(a_RigidBody != nullptr)
        {
            a_RigidBody->m_Body = body;
        }
    }

    void PhysicsSystem::createFixture(BoxCollider2D* a_Collider, RigidBody* a_RigidBody)
    {
        b2FixtureDef fixtureDefinition;

        fixtureDefinition.shape = a_Collider->getShape();
        //Temporary constant for consistency. No mass setting.
        fixtureDefinition.density = 1.0f;

        auto fixture = a_Collider->m_Body->CreateFixture(&fixtureDefinition);
        a_Collider->m_Fixture = fixture;
        if(a_RigidBody != nullptr)
        {
            a_RigidBody->m_Fixture = fixture;
        }
    }
}
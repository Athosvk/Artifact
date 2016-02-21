#include "PhysicsSystem.h"
#include "BoxCollider2D.h"
#include "RigidBody2D.h"
#include "../Core/EntitySystem.h"
#include "../Core/World.h"
#include "../Transform.h"
#include "../Game.h"

namespace BadEngine
{
    PhysicsSystem::PhysicsSystem(EntitySystem& a_EntitySystem, MessagingSystem& a_MessagingSystem)
        : System(a_EntitySystem, a_MessagingSystem),
        m_PhysicsWorld(a_MessagingSystem)
    {
    }

    void PhysicsSystem::registerListeners()
    {
        m_MessagingSystem.registerListener<ComponentAddedMessage<BoxCollider2D>>([this](const Message* a_Message)
        {
            onColliderAdd(static_cast<const ComponentAddedMessage<BoxCollider2D>*>(a_Message)->getAddedComponent());
        });
        m_MessagingSystem.registerListener<ComponentAddedMessage<RigidBody2D>>([this](const Message* a_Message)
        {
            onRigidBodyAdd(static_cast<const ComponentAddedMessage<RigidBody2D>*>(a_Message)->getAddedComponent());
        });
        m_MessagingSystem.registerListener<FixedUpdateMessage>([this](const Message*)
        {
            fixedUpdate();
        });
    }

    void PhysicsSystem::fixedUpdate()
    {
        for(auto collider : m_EntitySystem.getComponentsOfType<BoxCollider2D>())
        {
            collider->onPrePhysicsUpdate();
        }
        m_PhysicsWorld.fixedUpdate();
        updateTransforms();
    }

    void PhysicsSystem::updateTransforms()
    {
        for(auto rigidBody : m_EntitySystem.getComponentsOfType<RigidBody2D>())
        {
            rigidBody->updateState();
        }
    }

    void PhysicsSystem::onColliderAdd(BoxCollider2D* a_Collider)
    {
        auto rigidBody = a_Collider->getComponent<RigidBody2D>();
        if(rigidBody != nullptr)
        {
            a_Collider->m_Body = rigidBody->m_Body;
        }
        else
        {
            m_PhysicsWorld.emplace(a_Collider);
        }
    }

    void PhysicsSystem::onRigidBodyAdd(RigidBody2D* a_RigidBody)
    {
        auto collider = a_RigidBody->getComponent<BoxCollider2D>();
        if(collider != nullptr)
        {
             collider->m_Body->SetType(b2BodyType::b2_dynamicBody);
             a_RigidBody->m_Body = collider->m_Body;
        }
        else
        {
            m_PhysicsWorld.emplace(a_RigidBody);
        }
    }
}
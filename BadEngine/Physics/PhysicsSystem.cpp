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
        m_MessagingSystem.registerListener<FixedUpdateMessage>([this](const Message* a_Message)
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
        auto rigidBody = m_Uninitialised[a_Collider->getGameObject().getID()];
        m_PhysicsWorld.emplace(a_Collider, rigidBody);
        if(rigidBody != nullptr)
        {
            m_Uninitialised.erase(a_Collider->getGameObject().getID());
        }
    }

    void PhysicsSystem::onRigidBodyAdd(RigidBody2D* a_RigidBody)
    {
        auto collider = a_RigidBody->getComponent<BoxCollider2D>();
        if(collider != nullptr)
        {
            m_PhysicsWorld.emplace(collider, a_RigidBody);
        }
        else
        {
            m_Uninitialised[a_RigidBody->getGameObject().getID()] = a_RigidBody;
        }
    }
}
#include "PhysicsSystem.h"
#include "../Core/EntitySystem.h"
#include "RigidBody.h"
#include "../Transform.h"

namespace BadEngine
{
    PhysicsSystem::PhysicsSystem(EntitySystem& a_EnitySystem)
        : System(a_EnitySystem)
    {
    }

    void PhysicsSystem::sendMessage(const Message* a_Message)
    {
        switch(a_Message->getType())
        {
        case EMessageType::FixedUpdate:
            fixedUpdate();
        }
    }

    void PhysicsSystem::fixedUpdate()
    {
        updatePositions();
    }

    void PhysicsSystem::updatePositions()
    {
        for(auto rigidBody : m_EntitySystem.getComponentsOfType<RigidBody>())
        {
            auto transform = rigidBody->getComponent<Transform>();
            transform->setPosition(transform->getPosition() + rigidBody->Velocity);
        }
    }
}

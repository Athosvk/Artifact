#include <glm/gtx/vector_angle.hpp>

#include "../Core/EntitySystem.h"
#include "../Transform.h"
#include "../Core/World.h"
#include "MovementSystem.h"
#include "MovementComponent.h"
#include "../MathHelper.h"

namespace BadEngine
{
    MovementSystem::MovementSystem(BadEngine::EntitySystem& a_EntitySystem, BadEngine::MessagingSystem& a_MessagingSystem)
        : System(a_EntitySystem, a_MessagingSystem)
    {
    }

    void MovementSystem::registerListeners()
    {
        m_MessagingSystem.registerListener<FixedUpdateMessage>([=](const Message* a_Message)
        {
            updatePositions();
        });
    }

    void MovementSystem::updatePositions()
    {
        for(auto movement : m_EntitySystem.getComponentsOfType<MovementComponent>())
        {
            auto transform = movement->getComponent<Transform>();
            if(movement->Direction != glm::vec2(0, 0))
            {
                transform->translate(glm::normalize(movement->Direction) * movement->Speed);
                transform->setRotation(MathHelper::directionToAngle(movement->Direction));
            }
        }
    }
}
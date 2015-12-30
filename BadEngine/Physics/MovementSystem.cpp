#include "../Core/EntitySystem.h"
#include "../Transform.h"

#include "MovementSystem.h"
#include "MovementComponent.h"

namespace BadEngine
{
    MovementSystem::MovementSystem(BadEngine::EntitySystem& a_EntitySystem)
        : System(a_EntitySystem)
    {
    }

    void MovementSystem::sendMessage(const BadEngine::Message* a_Message)
    {
        switch(a_Message->getType())
        {
        case BadEngine::EMessageType::FixedUpdate:
            updatePositions();
        default:
            break;
        }
    }

    void MovementSystem::updatePositions()
    {
        for(auto movement : m_EntitySystem.getComponentsOfType<MovementComponent>())
        {
            auto transform = movement->getComponent<Transform>();
            if(movement->Direction != glm::vec2(0, 0))
            {
                transform->translate(glm::normalize(movement->Speed * movement->Direction));
            }
        }
    }
}
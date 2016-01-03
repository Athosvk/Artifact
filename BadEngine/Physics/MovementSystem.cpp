#include "../Core/EntitySystem.h"
#include "../Transform.h"

#include "MovementSystem.h"
#include "MovementComponent.h"

namespace BadEngine
{
    MovementSystem::MovementSystem(BadEngine::EntitySystem& a_EntitySystem, BadEngine::MessagingSystem& a_MessagingSystem)
        : System(a_EntitySystem, a_MessagingSystem)
    {
    }

    void MovementSystem::registerListeners()
    {
        
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
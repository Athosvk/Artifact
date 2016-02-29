#include <BadEngine/Core/World.h>
#include <BadEngine/Transform.h>

#include "ZombieBehaviourSystem.h"
#include "ZombieBehaviour.h"
#include "../Player/PlayerComponent.h"

ZombieBehaviourSystem::ZombieBehaviourSystem(BadEngine::EntitySystem& a_EntitySystem, 
    BadEngine::MessagingSystem& a_MessagingSystem)
    : System(a_EntitySystem, a_MessagingSystem)
{
}

void ZombieBehaviourSystem::registerListeners()
{
    m_MessagingSystem.registerListener<BadEngine::UpdateMessage>([this](const BadEngine::Message*)
    {
        update();
    });
}

void ZombieBehaviourSystem::update()
{
    for(auto behaviour : m_EntitySystem.getComponentsOfType<ZombieBehaviour>())
    {
        auto distance = glm::length(behaviour->getComponent<BadEngine::Transform>()->getPosition()
            - getPlayerPosition());
        if(distance <= behaviour->AttackRadius)
        {
            behaviour->setState(EBehaviourstate::Attack);
        }
        else
        {
            behaviour->setState(EBehaviourstate::Follow);
        }
    }
}

glm::vec2 ZombieBehaviourSystem::getPlayerPosition() const
{
    return m_EntitySystem.getComponentsOfType<PlayerComponent>()[0]->
        getComponent<BadEngine::Transform>()->getPosition();
}

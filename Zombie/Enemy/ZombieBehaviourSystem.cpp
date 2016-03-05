#include <Artifact/Core/World.h>
#include <Artifact/Transform.h>

#include "ZombieBehaviourSystem.h"
#include "ZombieBehaviour.h"
#include "../Player/PlayerComponent.h"

ZombieBehaviourSystem::ZombieBehaviourSystem(Artifact::EntitySystem& a_EntitySystem, 
    Artifact::MessagingSystem& a_MessagingSystem)
    : System(a_EntitySystem, a_MessagingSystem)
{
}

void ZombieBehaviourSystem::registerListeners()
{
    m_MessagingSystem.registerListener<Artifact::UpdateMessage>([this](const Artifact::Message*)
    {
        update();
    });
}

void ZombieBehaviourSystem::update()
{
    for(auto behaviour : m_EntitySystem.getComponentsOfType<ZombieBehaviour>())
    {
        auto distance = glm::length(behaviour->getComponent<Artifact::Transform>()->getPosition()
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
        getComponent<Artifact::Transform>()->getPosition();
}

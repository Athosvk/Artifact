#include <Artifact/Core/World.h>

#include "AttackSystem.h"
#include "AttackComponent.h"
#include "../HealthComponent.h"

AttackSystem::AttackSystem(Artifact::EntitySystem& a_EntitySystem, Artifact::MessagingSystem& a_MessagingSystem)
    : System(a_EntitySystem, a_MessagingSystem)
{
}

void AttackSystem::registerListeners()
{
    m_MessagingSystem.registerListener<Artifact::UpdateMessage>([this](const Artifact::Message*)
    {
        update();
    });
}

void AttackSystem::update()
{
    for(auto attackComponent : m_EntitySystem.getComponentsOfType<AttackComponent>())
    {
        if(attackComponent->canAttack())
        {
            auto playerHealth = getCurrentPlayer()->getComponent<HealthComponent>();
            playerHealth->dealDamage(attackComponent->Damage);
            attackComponent->startTimer();
        }
    }
}

PlayerComponent* AttackSystem::getCurrentPlayer() const
{
    return m_EntitySystem.getComponentsOfType<PlayerComponent>()[0];
}

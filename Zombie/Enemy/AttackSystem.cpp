#include <BadEngine/Core/World.h>

#include "AttackSystem.h"
#include "AttackComponent.h"
#include "../HealthComponent.h"

AttackSystem::AttackSystem(BadEngine::EntitySystem& a_EntitySystem, BadEngine::MessagingSystem& a_MessagingSystem)
    : System(a_EntitySystem, a_MessagingSystem)
{
}

void AttackSystem::registerListeners()
{
    m_MessagingSystem.registerListener<BadEngine::UpdateMessage>([this](const BadEngine::Message*)
    {
        update();
    });
}

void AttackSystem::update()
{
    for(auto& attackComponent : m_EntitySystem.getComponentsOfType<AttackComponent>())
    {
        if(attackComponent->DelayTimer->TimerState == ETimerState::Done)
        {
            auto playerHealth = getCurrentPlayer()->getComponent<HealthComponent>();
            playerHealth->dealDamage(attackComponent->Damage);
            attackComponent->DelayTimer->start();
        }
    }
}

PlayerComponent* AttackSystem::getCurrentPlayer() const
{
    return m_EntitySystem.getComponentsOfType<PlayerComponent>()[0];
}

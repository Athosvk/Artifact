#include <BadEngine/Core/EntitySystem.h>
#include <BadEngine/Physics/CollisionMessages.h>

#include "HealthSystem.h"
#include "HealthComponent.h"
#include "DamageComponent.h"

HealthSystem::HealthSystem(BadEngine::EntitySystem& a_EntitySystem, BadEngine::MessagingSystem& a_MessagingSystem)
    : System(a_EntitySystem, a_MessagingSystem)
{
}

void HealthSystem::registerListeners()
{
    m_MessagingSystem.registerListener<BadEngine::ComponentAddedMessage<HealthComponent>>([this](const BadEngine::Message* a_Message)
    {
        registerTriggerListener(static_cast<const BadEngine::ComponentAddedMessage<HealthComponent>*>(a_Message)
            ->getAddedComponent()->getGameObject());
    });
}

void HealthSystem::registerTriggerListener(BadEngine::GameObject a_GameObject)
{
    m_MessagingSystem.registerListener<BadEngine::TriggerEnter2DMessage>([this](const BadEngine::Message* a_Message)
    {
        auto collisionMessage = static_cast<const BadEngine::TriggerEnter2DMessage*>(a_Message);
        onTriggerEnter(collisionMessage->getCollider(), collisionMessage->getOther());
    }, a_GameObject);
}

void HealthSystem::onTriggerEnter(BadEngine::BoxCollider2D* a_Object, BadEngine::BoxCollider2D* a_Other)
{
    auto damageComponent = a_Other->getComponent<DamageComponent>();
    if(damageComponent != nullptr)
    {
        dealDamage(a_Object->getComponent<HealthComponent>(), damageComponent->Damage);
    }
}

void HealthSystem::dealDamage(HealthComponent* a_Health, int a_Damage)
{
    a_Health->CurrentHealth -= 1;
    if(a_Health->CurrentHealth <= 0)
    {
        onDeath(a_Health);
    }
}

void HealthSystem::onDeath(HealthComponent* a_Health)
{
    a_Health->getGameObject().deactivate();
}

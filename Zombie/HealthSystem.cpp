#include <BadEngine/Core/EntitySystem.h>
#include <BadEngine/Physics/CollisionMessages.h>

#include "HealthSystem.h"
#include "HealthComponent.h"

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
        onTriggerEnter(collisionMessage->getCollider());
    }, a_GameObject);
}

void HealthSystem::onTriggerEnter(BadEngine::BoxCollider2D* a_Object)
{
    auto health = a_Object->getComponent<HealthComponent>();
    health->CurrentHealth -= 1;
    if(health->CurrentHealth <= 0)
    {
        onDeath(health);
    }
}

void HealthSystem::onDeath(HealthComponent* a_Health)
{
    a_Health->getGameObject().deactivate();
}

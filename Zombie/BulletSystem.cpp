#include <BadEngine/Physics/CollisionMessages.h>
#include <BadEngine/Core/EntitySystem.h>
#include <BadEngine/Core/Component.h>
#include <BadEngine/Physics/BoxCollider2D.h>

#include "BulletSystem.h"
#include "BulletComponent.h"
#include "TagComponent.h"
#include "HealthComponent.h"

BulletSystem::BulletSystem(BadEngine::EntitySystem& a_EntitySystem, BadEngine::MessagingSystem& a_MesssagingSystem)
    : System(a_EntitySystem, a_MesssagingSystem)
{
}

void BulletSystem::registerListeners()
{
    m_MessagingSystem.registerListener<BadEngine::ComponentAddedMessage<BulletComponent>>(
        [this](const BadEngine::Message* a_Message)
    {
        auto addedComponent = static_cast<const BadEngine::ComponentAddedMessage<BulletComponent>*>(a_Message)
            ->getAddedComponent();
        registerCollisionListener(addedComponent->getGameObject());
    });
}

void BulletSystem::registerCollisionListener(const BadEngine::GameObject a_Target)
{
    m_MessagingSystem.registerListener<BadEngine::TriggerEnter2DMessage>([this](const BadEngine::Message* a_Message)
    {
        auto triggerMessage = static_cast<const BadEngine::TriggerEnter2DMessage*>(a_Message);
        onTriggerEnter(triggerMessage->getCollider(), triggerMessage->getOther());
    }, a_Target);
}

void BulletSystem::onTriggerEnter(BadEngine::BoxCollider2D* a_Collider, BadEngine::BoxCollider2D* a_Other)
{
    auto collidingTag = a_Other->getComponent<TagComponent>();
    if(collidingTag != nullptr)
    {
        auto bullet = a_Collider->getComponent<BulletComponent>();
        if(BadEngine::EnumUtility::hasFlag(bullet->TargetTag, collidingTag->Type))
        {
            HealthComponent* targetHealth = a_Other->getComponent<HealthComponent>();
            if(targetHealth != nullptr)
            {
                targetHealth->dealDamage(bullet->Damage);
                bullet->getGameObject().deactivate();
            }
        }
        else if(BadEngine::EnumUtility::hasFlag(bullet->BlockingTag, collidingTag->Type))
        {
            bullet->getGameObject().deactivate();
        }
    }
}

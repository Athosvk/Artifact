#include <Artifact/Physics/CollisionMessages.h>
#include <Artifact/Core/EntitySystem.h>
#include <Artifact/Core/Component.h>
#include <Artifact/Physics/BoxCollider2D.h>

#include "BulletSystem.h"
#include "BulletComponent.h"
#include "TagComponent.h"
#include "HealthComponent.h"

BulletSystem::BulletSystem(Artifact::EntitySystem& a_EntitySystem, Artifact::MessagingSystem& a_MesssagingSystem)
    : System(a_EntitySystem, a_MesssagingSystem)
{
}

void BulletSystem::registerListeners()
{
    m_MessagingSystem.registerListener<Artifact::ComponentAddedMessage<BulletComponent>>(
        [this](const Artifact::Message* a_Message)
    {
        auto addedComponent = static_cast<const Artifact::ComponentAddedMessage<BulletComponent>*>(a_Message)
            ->getAddedComponent();
        registerCollisionListener(addedComponent->getGameObject());
    });
}

void BulletSystem::registerCollisionListener(const Artifact::GameObject a_Target)
{
    m_MessagingSystem.registerListener<Artifact::CollisionEnter2DMessage>([this](const Artifact::Message* a_Message)
    {
        auto triggerMessage = static_cast<const Artifact::CollisionEnter2DMessage*>(a_Message);
        onCollisionEnter(triggerMessage->getCollider(), triggerMessage->getOther());
    }, a_Target);
}

void BulletSystem::onCollisionEnter(Artifact::BoxCollider2D* a_Collider, Artifact::BoxCollider2D* a_Other)
{
    auto collidingTag = a_Other->getComponent<TagComponent>();
    if(collidingTag != nullptr)
    {
        auto bullet = a_Collider->getComponent<BulletComponent>();
        if(Artifact::EnumUtility::hasFlag(bullet->TargetTag, collidingTag->Type))
        {
            HealthComponent* targetHealth = a_Other->getComponent<HealthComponent>();
            if(targetHealth != nullptr)
            {
                targetHealth->dealDamage(bullet->Damage);
                bullet->getGameObject().deactivate();
            }
        }
        else if(Artifact::EnumUtility::hasFlag(bullet->BlockingTag, collidingTag->Type))
        {
            bullet->getGameObject().deactivate();
        }
    }
}

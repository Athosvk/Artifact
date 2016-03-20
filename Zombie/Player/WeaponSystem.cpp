#include <Artifact/Core/EntitySystem.h>
#include <Artifact/Physics/RigidBody2D.h>
#include <Artifact/MathHelper.h>
#include <Artifact/Audio/AudioSource.h>

#include "WeaponSystem.h"
#include "WeaponComponent.h"
#include "../BulletComponent.h"

FireWeaponMessage::FireWeaponMessage(WeaponComponent* a_WeaponComponent)
    : m_WeaponComponent(a_WeaponComponent)
{ 
}

WeaponComponent* FireWeaponMessage::getWeapon() const
{
    return m_WeaponComponent;
}

WeaponSystem::WeaponSystem(Artifact::EntitySystem& a_EntitySystem, Artifact::MessagingSystem& a_MessagingSystem)
    : System(a_EntitySystem, a_MessagingSystem),
    m_BulletPool(m_EntitySystem)
{
}

void WeaponSystem::registerListeners()
{
    m_MessagingSystem.registerListener<FireWeaponMessage>([=](const Artifact::Message* a_Message)
    {
        tryFire(static_cast<const FireWeaponMessage*>(a_Message));
    });
}

void WeaponSystem::tryFire(const FireWeaponMessage* a_FireMessage)
{
    auto weapon = a_FireMessage->getWeapon();
    if(weapon->FireDelayTimer->TimerState == ETimerState::Done)
    {
        fire(weapon);
    }
}

void WeaponSystem::fire(WeaponComponent* a_Weapon)
{
    createBullet(a_Weapon->getComponent<Artifact::Transform>());
    a_Weapon->getComponent<Artifact::AudioSource>()->play();
    a_Weapon->FireDelayTimer->start();
}

void WeaponSystem::createBullet(const Artifact::Transform* a_MuzzleTransform)
{
    auto offset = Artifact::MathHelper::rotate(glm::vec2(0.4f, -0.25f), 
        a_MuzzleTransform->getRotation(), glm::vec2(0.0f));

    auto bullet = m_BulletPool.getEntity();

    auto bulletTransform = bullet.getComponent<Artifact::Transform>();
    bulletTransform->setPosition(a_MuzzleTransform->getPosition() + offset);
    bulletTransform->setRotation(a_MuzzleTransform->getRotation());
    auto targetDirection = Artifact::MathHelper::directionFromAngle(a_MuzzleTransform->getRotation());
    auto bulletSpeed = bullet.getComponent<BulletComponent>()->Speed;
    bullet.getComponent<Artifact::RigidBody2D>()->setVelocity(targetDirection * bulletSpeed);
}

#include <BadEngine/Core/EntitySystem.h>
#include <BadEngine/Physics/RigidBody2D.h>
#include <BadEngine/MathHelper.h>

#include "WeaponSystem.h"
#include "../Bullet.h"
#include "../BulletComponent.h"

FireWeaponMessage::FireWeaponMessage(WeaponComponent* a_WeaponComponent)
    : m_WeaponComponent(a_WeaponComponent)
{ 
}

WeaponComponent* FireWeaponMessage::getWeapon() const
{
    return m_WeaponComponent;
}

WeaponSystem::WeaponSystem(BadEngine::EntitySystem& a_EntitySystem, BadEngine::MessagingSystem& a_MessagingSystem)
    : System(a_EntitySystem, a_MessagingSystem)
{
}

void WeaponSystem::registerListeners()
{
    m_MessagingSystem.registerListener<FireWeaponMessage>([=](const BadEngine::Message* a_Message)
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
    createBullet(a_Weapon->getComponent<BadEngine::Transform>());
    a_Weapon->FireDelayTimer->start();
}

void WeaponSystem::createBullet(const BadEngine::Transform* a_MuzzleTransform)
{
    auto bullet = m_EntitySystem.createEntity<Bullet>();
    auto bulletTransform = bullet.getComponent<BadEngine::Transform>();
    bulletTransform->setPosition(a_MuzzleTransform->getPosition());
    bulletTransform->setRotation(a_MuzzleTransform->getRotation());
    auto targetDirection = BadEngine::MathHelper::directionFromAngle(a_MuzzleTransform->getRotation());
    auto bulletSpeed = bullet.getComponent<BulletComponent>()->Speed;
    bullet.getComponent<BadEngine::RigidBody2D>()->setVelocity(targetDirection * bulletSpeed);
}

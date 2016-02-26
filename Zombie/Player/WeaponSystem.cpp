#include <BadEngine/Core/EntitySystem.h>
#include <BadEngine/Physics/RigidBody2D.h>
#include <BadEngine/MathHelper.h>

#include "WeaponSystem.h"
#include "../Bullet.h"

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
    for(int i = 0; i < 1; i++)
    {
        auto bullet = m_EntitySystem.createEntity<Bullet>();
        bullet.getComponent<BadEngine::Transform>()->setPosition(a_Weapon->MuzzleTransform->getPosition());
        auto targetDirection = BadEngine::MathHelper::directionFromAngle(a_Weapon->getComponent<BadEngine::Transform>()->getRotation());
        const auto bulletSpeed = 10.0f;
        bullet.getComponent<BadEngine::RigidBody2D>()->setVelocity(targetDirection * bulletSpeed);
    }
    a_Weapon->FireDelayTimer->start();
}
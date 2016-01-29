#include <BadEngine/Core/EntitySystem.h>
#include <BadEngine/Physics/MovementComponent.h>
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
    auto bullet = m_EntitySystem.createEntity<Bullet>();
    bullet.getComponent<BadEngine::Transform>()->setPosition(a_Weapon->MuzzleTransform->getPosition());
    auto targetDirection = BadEngine::MathHelper::directionFromAngle(a_Weapon->getComponent<BadEngine::Transform>()->LocalRotation);
    bullet.getComponent<BadEngine::MovementComponent>()->Direction = targetDirection;
    a_Weapon->FireDelayTimer->start();
}
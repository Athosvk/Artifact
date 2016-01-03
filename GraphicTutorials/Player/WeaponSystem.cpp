#include <BadEngine/Core/EntitySystem.h>

#include "WeaponSystem.h"
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
        fire(static_cast<const FireWeaponMessage*>(a_Message));
    });
}

void WeaponSystem::update()
{

}

void WeaponSystem::fire(const FireWeaponMessage* a_Weapon)
{
}

void WeaponSystem::startReload(BulletComponent* a_BulletComponent)
{

}
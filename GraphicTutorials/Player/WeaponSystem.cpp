#include <BadEngine/Core/EntitySystem.h>

#include "WeaponSystem.h"
#include "../BulletComponent.h"

WeaponSystem::WeaponSystem(BadEngine::EntitySystem& a_EntitySystem)
    : System(a_EntitySystem)
{
}

void WeaponSystem::sendMessage(const BadEngine::Message* a_Message)
{
    switch(a_Message->getType())
    {
    default:
        break;
    }
}

void WeaponSystem::update()
{

}

void WeaponSystem::fire()
{
    auto newEntity = m_EntitySystem.createEntity().addComponent<BulletComponent>();
    //bullet->fire(m_Transform.getPosition() + m_FireOffset, m_Mouse.getWorldPosition());
}

void WeaponSystem::startReload(BulletComponent* a_BulletComponent)
{

}
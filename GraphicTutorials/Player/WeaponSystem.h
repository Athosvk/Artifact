#pragma once
#include <BadEngine/Core/System.h>

#include "WeaponComponent.h" 

class BulletComponent;

class FireWeaponMessage : public BadEngine::Message
{
    WeaponComponent* m_WeaponComponent;

public:
    FireWeaponMessage(WeaponComponent* a_WeaponComponent);

    WeaponComponent* getWeapon() const;
};

class WeaponSystem : public BadEngine::System
{
public:
    WeaponSystem(BadEngine::EntitySystem& a_EntitySystem, BadEngine::MessagingSystem& a_MessagingSystem);

    virtual void registerListeners() override;
private:
    void tryFire(const FireWeaponMessage* a_FireMessage);
    void fire(WeaponComponent* a_Weapon);
};


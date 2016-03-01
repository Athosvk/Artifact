#pragma once
#include <Artifact/Core/System.h>

#include "WeaponComponent.h" 

class BulletComponent;

class FireWeaponMessage : public Artifact::Message
{
    WeaponComponent* m_WeaponComponent;

public:
    FireWeaponMessage(WeaponComponent* a_WeaponComponent);

    WeaponComponent* getWeapon() const;
};

class WeaponSystem : public Artifact::System
{
public:
    WeaponSystem(Artifact::EntitySystem& a_EntitySystem, Artifact::MessagingSystem& a_MessagingSystem);

    virtual void registerListeners() override;
private:
    void tryFire(const FireWeaponMessage* a_FireMessage);
    void fire(WeaponComponent* a_Weapon);
    void createBullet(const Artifact::Transform* a_MuzzleTransform);
};


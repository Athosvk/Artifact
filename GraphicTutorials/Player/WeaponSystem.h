#pragma once
#include <BadEngine/Core/System.h>

class BulletComponent;

class WeaponSystem : BadEngine::System
{
public:
    WeaponSystem(BadEngine::EntitySystem& a_EntitySystem, BadEngine::MessagingSystem& a_MessagingSystem);

    virtual void registerListeners() override;
private:
    void update();
    void fire();
    void startReload(BulletComponent* a_BulletComponent);
};


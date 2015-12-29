#pragma once
#include <BadEngine/Core/System.h>

class BulletComponent;

class WeaponSystem : BadEngine::System
{
public:
    WeaponSystem(BadEngine::EntitySystem& a_EntitySystem);

    virtual void sendMessage(const BadEngine::Message* a_Message) override;

private:
    void update();
    void fire();
    void startReload(BulletComponent* a_BulletComponent);
};


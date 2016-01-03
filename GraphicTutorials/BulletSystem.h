#pragma once
#include <BadEngine/Core/System.h>

#include "BulletComponent.h"

class BulletSystem : public BadEngine::System
{
public:
    BulletSystem(BadEngine::EntitySystem& a_EntitySystem, BadEngine::MessagingSystem a_MessagingSystem);

    virtual void registerListeners() override;

private:
    void update();
};


#pragma once
#include <BadEngine/Core/System.h>

#include "BulletComponent.h"

class BulletSystem : public BadEngine::System
{
public:
    BulletSystem(BadEngine::EntitySystem& a_EntitySystem);

public:
    virtual void sendMessage(const BadEngine::Message* a_Message) override;

private:
    void update();
};


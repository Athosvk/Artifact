#pragma once
#include <BadEngine/Core/System.h>

#include "../Player/PlayerComponent.h"

class AttackSystem : public BadEngine::System
{
public:
    AttackSystem(BadEngine::EntitySystem& a_EntitySystem, BadEngine::MessagingSystem& a_MessagingSystem);

    virtual void registerListeners() override;
private:
    void update();
    PlayerComponent* getCurrentPlayer() const;
};


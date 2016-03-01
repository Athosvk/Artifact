#pragma once
#include <Artifact/Core/System.h>

#include "../Player/PlayerComponent.h"

class AttackSystem : public Artifact::System
{
public:
    AttackSystem(Artifact::EntitySystem& a_EntitySystem, Artifact::MessagingSystem& a_MessagingSystem);

    virtual void registerListeners() override;
private:
    void update();
    PlayerComponent* getCurrentPlayer() const;
};


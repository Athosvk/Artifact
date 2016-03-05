#pragma once
#include <Artifact/Core/System.h>

class PlayerComponent;

class FollowSystem : public Artifact::System
{
public:
    FollowSystem(Artifact::EntitySystem& a_EntitySystem, Artifact::MessagingSystem& a_MessagingSystem);

    virtual void registerListeners() override;
private:
    void updateVelocities();
    PlayerComponent* getCurrentPlayer();
};


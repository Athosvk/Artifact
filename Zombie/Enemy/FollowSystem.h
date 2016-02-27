#pragma once
#include <BadEngine/Core/System.h>

class PlayerComponent;

class FollowSystem : public BadEngine::System
{
public:
    FollowSystem(BadEngine::EntitySystem& a_EntitySystem, BadEngine::MessagingSystem& a_MessagingSystem);

    virtual void registerListeners() override;
private:
    void updateVelocities();
    PlayerComponent* getCurrentPlayer();
};


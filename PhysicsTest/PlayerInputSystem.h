#pragma once
#include <BadEngine/Core/System.h>

class PlayerInputComponent;

class PlayerInputSystem : public BadEngine::System
{
public:
    PlayerInputSystem(BadEngine::EntitySystem& a_EntitySystem, BadEngine::MessagingSystem& a_MessagingSystem);

    virtual void registerListeners() override;

private:
    void handleInput();
    void updatePlayerMovement(PlayerInputComponent* a_Player);
};


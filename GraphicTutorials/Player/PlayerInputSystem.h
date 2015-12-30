#pragma once
#include <BadEngine/Core/System.h>

class PlayerInputComponent;

class PlayerInputSystem : public BadEngine::System
{
public:
    PlayerInputSystem(BadEngine::EntitySystem& a_EntitySystem);

    virtual void sendMessage(const BadEngine::Message* a_Message) override;

private:
    void handleInput();
    void updatePlayerMovement(PlayerInputComponent* a_Player);
    void updateFireState(PlayerInputComponent* a_Player);
};


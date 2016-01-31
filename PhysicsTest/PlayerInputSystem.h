#pragma once
#include <BadEngine/Core/System.h>
#include <BadEngine/Physics/BoxCollider2D.h>

class PlayerInputComponent;

class PlayerInputSystem : public BadEngine::System
{
public:
    PlayerInputSystem(BadEngine::EntitySystem& a_EntitySystem, BadEngine::MessagingSystem& a_MessagingSystem);

    virtual void registerListeners() override;

private:
    void handleInput();
    void updatePlayerMovement(PlayerInputComponent* a_Player);
    void onCollisionEnter(BadEngine::BoxCollider2D* a_Collider, BadEngine::BoxCollider2D* a_Other);
};


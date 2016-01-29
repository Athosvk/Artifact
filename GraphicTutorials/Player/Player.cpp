#include <BadEngine/Core/EntitySystem.h>
#include <BadEngine/IO/ResourceManager.h>
#include <BadEngine/Physics/MovementComponent.h>

#include "Player.h"
#include "PlayerInputComponent.h"
#include "WeaponComponent.h"

Player::Player(unsigned a_ID, BadEngine::EntitySystem& a_EntitySystem)
    : GameObject(a_ID, a_EntitySystem)
{
    auto renderer = addComponent<BadEngine::SpriteRenderer>();
    renderer->setTexture(BadEngine::ResourceManager::getTexture("Textures/Top_Down_Survivor/handgun/idle/survivor-idle_handgun_0.png"));

    auto inputController = addComponent<PlayerInputComponent>();
    auto weapon = addComponent<WeaponComponent>();

    inputController->MoveUpKey = BadEngine::KeyCode::W;
    inputController->MoveDownKey = BadEngine::KeyCode::S;
    inputController->MoveLeftKey = BadEngine::KeyCode::A;
    inputController->MoveRightKey = BadEngine::KeyCode::D;
    inputController->FireKey = BadEngine::KeyCode::Space;
    inputController->Weapon = weapon;

    renderer->Width = 1;
    renderer->Height = 1;

    weapon->FireDelayTimer->Duration = 0.5f;
    weapon->MuzzleTransform = getComponent<BadEngine::Transform>();
    
    auto movement = addComponent<BadEngine::MovementComponent>();
    movement->Speed = 3.5f;
}
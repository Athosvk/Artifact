#include <BadEngine/Core/EntitySystem.h>
#include <BadEngine/IO/ResourceManager.h>
#include <BadEngine/Physics/MovementComponent.h>

#include "Player.h"
#include "PlayerInputComponent.h"
#include "WeaponComponent.h"

Player::Player(BadEngine::EntitySystem& a_EntitySystem)
    : m_PlayerEntity(a_EntitySystem.createEntity())
{
    auto renderer = m_PlayerEntity.addComponent<BadEngine::SpriteRenderer>();
    renderer->setTexture(BadEngine::ResourceManager::getTexture("Textures/PNG/CharacterLeft_Standing.png"));

    auto inputController = m_PlayerEntity.addComponent<PlayerInputComponent>();

    inputController->MoveUpKey = BadEngine::KeyCode::W;
    inputController->MoveDownKey = BadEngine::KeyCode::S;
    inputController->MoveLeftKey = BadEngine::KeyCode::A;
    inputController->MoveRightKey = BadEngine::KeyCode::D;
    inputController->FireKey = BadEngine::KeyCode::Space;
    inputController->Weapon = m_PlayerEntity.addComponent<WeaponComponent>();;
    
    auto movement = m_PlayerEntity.addComponent<BadEngine::MovementComponent>();
    movement->Speed = 3.5f;
}
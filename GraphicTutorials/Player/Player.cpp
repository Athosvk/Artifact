#include <BadEngine/Core/EntitySystem.h>
#include <BadEngine/IO/ResourceManager.h>

#include "Player.h"
#include "PlayerInputComponent.h"

Player::Player(BadEngine::EntitySystem& a_EntitySystem)
    : m_PlayerEntity(a_EntitySystem.createEntity())
{
    auto renderer = m_PlayerEntity.addComponent<BadEngine::SpriteRenderer>();
    renderer->setTexture(BadEngine::ResourceManager::getTexture("Textures/PNG/CharacterLeft_Standing.png"));

    auto inputController = m_PlayerEntity.addComponent<PlayerInputComponent>();

    inputController->MoveForwardKey = BadEngine::KeyCode::W;
    inputController->MoveBackwardKey = BadEngine::KeyCode::S;
    inputController->MoveLeftKey = BadEngine::KeyCode::A;
    inputController->MoveRightKey = BadEngine::KeyCode::D;
    inputController->FireKey = BadEngine::KeyCode::Space;
}
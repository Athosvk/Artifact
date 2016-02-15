#include <BadEngine/Core/EntitySystem.h>
#include <BadEngine/IO/ResourceManager.h>
#include <BadEngine/Physics/RigidBody2D.h>
#include <BadEngine/Physics/BoxCollider2D.h>
#include <BadEngine/Transform.h>

#include "Player.h"
#include "PlayerInputComponent.h"

Player::Player(unsigned a_ID, BadEngine::EntitySystem& a_EntitySystem)
    : GameObject(a_ID, a_EntitySystem)
{
    auto renderer = addComponent<BadEngine::SpriteRenderer>();
    renderer->setTexture(BadEngine::ResourceManager::getTexture("Textures/Box.png"));

    auto inputController = addComponent<PlayerInputComponent>();

    inputController->MoveUpKey = BadEngine::KeyCode::W;
    inputController->MoveDownKey = BadEngine::KeyCode::S;
    inputController->MoveLeftKey = BadEngine::KeyCode::A;
    inputController->MoveRightKey = BadEngine::KeyCode::D;

    renderer->Width = 0.5f;
    renderer->Height = 0.5f;

    auto collider = addComponent<BadEngine::BoxCollider2D>();
    collider->setDimensions(glm::vec2(0.5f, 0.5f));
    auto rigidbody = addComponent<BadEngine::RigidBody2D>();
}
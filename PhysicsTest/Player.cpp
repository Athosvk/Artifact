#include <BadEngine/Core/EntitySystem.h>
#include <BadEngine/IO/ResourceManager.h>
#include <BadEngine/Physics/RigidBody.h>
#include <BadEngine/Physics/MovementComponent.h>
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

    renderer->Width = 1;
    renderer->Height = 1;

    auto transform = getComponent<BadEngine::Transform>();
    transform->setPosition(glm::vec2(transform->getPosition().x, transform->getPosition().y + 0.75));

    auto collider = addComponent<BadEngine::BoxCollider2D>();
    collider->setDimensions(glm::vec2(1, 1));
    auto rigidbody = addComponent<BadEngine::RigidBody>();
}
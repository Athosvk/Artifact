#include <Artifact/Core/EntitySystem.h>
#include <Artifact/IO/ResourceManager.h>
#include <Artifact/Physics/RigidBody2D.h>
#include <Artifact/Physics/BoxCollider2D.h>
#include <Artifact/Transform.h>

#include "Player.h"
#include "PlayerInputComponent.h"

Player::Player(unsigned a_ID, Artifact::EntitySystem& a_EntitySystem)
    : GameObject(a_ID, a_EntitySystem)
{
    auto renderer = addComponent<Artifact::SpriteRenderer>();
    renderer->setTexture(Artifact::ResourceManager::getTexture("Textures/Box.png"));

    auto inputController = addComponent<PlayerInputComponent>();

    inputController->MoveUpKey = Artifact::KeyCode::W;
    inputController->MoveDownKey = Artifact::KeyCode::S;
    inputController->MoveLeftKey = Artifact::KeyCode::A;
    inputController->MoveRightKey = Artifact::KeyCode::D;

    renderer->Width = 0.5f;
    renderer->Height = 0.5f;

    auto collider = addComponent<Artifact::BoxCollider2D>();
    collider->setDimensions(glm::vec2(0.5f, 0.5f));
    auto rigidbody = addComponent<Artifact::RigidBody2D>();
}
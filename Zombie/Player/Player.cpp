#include <Artifact/Core/EntitySystem.h>
#include <Artifact/IO/ResourceManager.h>
#include <Artifact/Physics/BoxCollider2D.h>
#include <Artifact/Physics/RigidBody2D.h>
#include <Artifact/Rendering/SpriteRenderer.h>
#include <Artifact/Audio/AudioSource.h>

#include "Player.h"
#include "PlayerInputComponent.h"
#include "WeaponComponent.h"
#include "PlayerComponent.h"
#include "../HealthComponent.h"
#include "../TagComponent.h"
#include "PlayerScoreComponent.h"

Player::Player(unsigned a_ID, Artifact::EntitySystem& a_EntitySystem)
    : GameObject(a_ID, a_EntitySystem)
{
    auto renderer = addComponent<Artifact::SpriteRenderer>();
    renderer->setTexture(Artifact::ResourceManager::getTexture("Textures/Top_Down_Survivor/handgun/idle/survivor-idle_handgun_0.png"));

    auto inputController = addComponent<PlayerInputComponent>();
    auto weapon = addComponent<WeaponComponent>();
    auto weaponSound = addComponent<Artifact::AudioSource>();
    weaponSound->Sound = Artifact::ResourceManager::getSound("Sounds/shots/cg1.wav");

    inputController->MoveUpKey = Artifact::KeyCode::W;
    inputController->MoveDownKey = Artifact::KeyCode::S;
    inputController->MoveLeftKey = Artifact::KeyCode::A;
    inputController->MoveRightKey = Artifact::KeyCode::D;
    inputController->FireKey = Artifact::KeyCode::Space;
    inputController->Weapon = weapon;

    renderer->Width = 1;
    renderer->Height = 1;
    renderer->Depth = 2.0f;

    weapon->FireDelayTimer->Duration = 0.5f;
    weapon->MuzzleTransform = getComponent<Artifact::Transform>();
    
    auto rigidBody = addComponent<Artifact::RigidBody2D>();
    auto collider = addComponent<Artifact::BoxCollider2D>();
    collider->setDimensions(glm::vec2(0.5f, 0.5f));
    collider->enableTriggerState();
    rigidBody->setGravityScale(0.0f);

    addComponent<PlayerComponent>();
    auto health = addComponent<HealthComponent>();

    const auto MaxHealth = 25u;
    health->initialise(MaxHealth);

    auto tag = addComponent<TagComponent>();
    tag->Type = EType::Player;

    addComponent<PlayerScoreComponent>();
}
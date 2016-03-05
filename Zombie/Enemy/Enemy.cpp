#include <Artifact/IO/ResourceManager.h>
#include <Artifact/Rendering/SpriteRenderer.h>
#include <Artifact/Core/EntitySystem.h>
#include <Artifact/Physics/BoxCollider2D.h>
#include <Artifact/Physics/RigidBody2D.h>

#include "Enemy.h"
#include "../HealthComponent.h"
#include "FollowComponent.h"
#include "../TagComponent.h"
#include "AttackComponent.h"
#include "../TimerComponent.h"
#include "ZombieBehaviour.h"
#include "../ScoreComponent.h"
#include "../CollisionLayers.h"

Enemy::Enemy(unsigned a_ID, Artifact::EntitySystem& a_EntitySystem)
    : GameObject(a_ID, a_EntitySystem)
{
    auto renderer = addComponent<Artifact::SpriteRenderer>();
    renderer->setTexture(Artifact::ResourceManager::getTexture("Textures/Zombie textures/skeleton-move_0.png"));
    renderer->Width = 1.0f;
    renderer->Height = 1.0f;

    const auto MaxHealth = 5u;
    auto health = addComponent<HealthComponent>();
    health->initialise(MaxHealth);
    health->OnDeath += [](HealthComponent* a_Health) {a_Health->getGameObject().deactivate(); };

    auto tag = addComponent<TagComponent>();
    tag->Type = EType::Enemy;

    auto collider = addComponent<Artifact::BoxCollider2D>();
    collider->setDimensions(glm::vec2(0.5f, 0.5f));
    collider->setLayer(static_cast<uint16>(ECollisionLayer::Enemy));
    collider->setMask(static_cast<uint16>(ECollisionLayer::All ^ (ECollisionLayer::Player | ECollisionLayer::Enemy)));

    auto followComponent = addComponent<FollowComponent>();
    followComponent->FollowSpeed = 0.5f;

    auto attackComponent = addComponent<AttackComponent>();
    attackComponent->setAttackInterval(1.0f);

    auto behaviour = addComponent<ZombieBehaviour>();

    auto score = addComponent<ScoreComponent>();
    score->Amount = 10;

    auto rigidBody = addComponent<Artifact::RigidBody2D>();
    rigidBody->setGravityScale(0.0f);
}
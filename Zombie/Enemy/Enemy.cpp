#include <BadEngine/IO/ResourceManager.h>
#include <BadEngine/Rendering/SpriteRenderer.h>
#include <BadEngine/Transform.h>
#include <BadEngine/Core/EntitySystem.h>
#include <BadEngine/Physics/BoxCollider2D.h>
#include <BadEngine/Physics/RigidBody2D.h>

#include "Enemy.h"
#include "../HealthComponent.h"
#include "FollowComponent.h"
#include "../TagComponent.h"
#include "AttackComponent.h"
#include "../TimerComponent.h"
#include "ZombieBehaviour.h"

Enemy::Enemy(unsigned a_ID, BadEngine::EntitySystem& a_EntitySystem)
    : GameObject(a_ID, a_EntitySystem)
{
    auto renderer = addComponent<BadEngine::SpriteRenderer>();
    renderer->setTexture(BadEngine::ResourceManager::getTexture("Textures/Zombie textures/skeleton-move_0.png"));
    renderer->Width = 1.0f;
    renderer->Height = 1.0f;

    const auto MaxHealth = 5u;
    auto health = addComponent<HealthComponent>();
    health->initialise(MaxHealth);
    health->OnDeath += [](HealthComponent* a_Health) {a_Health->getGameObject().deactivate(); };

    auto tag = addComponent<TagComponent>();
    tag->Type = EType::Enemy;

    auto collider = addComponent<BadEngine::BoxCollider2D>();
    collider->enableTriggerState();
    collider->setDimensions(glm::vec2(0.8f, 0.8f));

    auto followComponent = addComponent<FollowComponent>();
    followComponent->FollowSpeed = 0.5f;

    auto attackComponent = addComponent<AttackComponent>();
    attackComponent->setAttackInterval(1.0f);

    auto behaviour = addComponent<ZombieBehaviour>();
    behaviour->AttackComponent = attackComponent;
    behaviour->FollowComponent = followComponent;

    auto rigidBody = addComponent<BadEngine::RigidBody2D>();
    rigidBody->setGravityScale(0.0f);
}
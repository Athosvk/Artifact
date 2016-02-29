#include <BadEngine/Physics/RigidBody2D.h>
#include <BadEngine/Rendering/SpriteRenderer.h>
#include <BadEngine/IO/ResourceManager.h>
#include <BadEngine/Core/EntitySystem.h>
#include <BadEngine/Physics/BoxCollider2D.h>

#include "Bullet.h"
#include "TimerComponent.h"
#include "HealthComponent.h"
#include "BulletComponent.h"

Bullet::Bullet(unsigned a_ID, BadEngine::EntitySystem& a_EntitySystem)
    : GameObject(a_ID, a_EntitySystem)
{
    auto rigidBody = addComponent<BadEngine::RigidBody2D>();
    rigidBody->setGravityScale(0.0f);

    auto collider = addComponent<BadEngine::BoxCollider2D>();
    collider->setDimensions(glm::vec2(0.1f, 0.1f));
    collider->enableTriggerState();

    auto renderer = addComponent<BadEngine::SpriteRenderer>();
    renderer->Width = 0.1f;
    renderer->Height = 0.1f;
    renderer->setTexture(BadEngine::ResourceManager::getTexture("Textures/PNG/Bullet.png"));

    auto bulletComponent = addComponent<BulletComponent>();
    bulletComponent->Speed = 10.0f;
}
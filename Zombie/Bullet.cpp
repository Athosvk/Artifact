#include <Artifact/Physics/RigidBody2D.h>
#include <Artifact/Rendering/SpriteRenderer.h>
#include <Artifact/IO/ResourceManager.h>
#include <Artifact/Core/EntitySystem.h>
#include <Artifact/Physics/BoxCollider2D.h>

#include "Bullet.h"
#include "TimerComponent.h"
#include "HealthComponent.h"
#include "BulletComponent.h"
#include "CollisionLayers.h"

Bullet::Bullet(unsigned a_ID, Artifact::EntitySystem& a_EntitySystem)
    : GameObject(a_ID, a_EntitySystem)
{
    auto rigidBody = addComponent<Artifact::RigidBody2D>();
    rigidBody->setGravityScale(0.0f);

    auto collider = addComponent<Artifact::BoxCollider2D>();
    collider->setDimensions(glm::vec2(0.1f, 0.1f));
    collider->setLayer(static_cast<uint16>(ECollisionLayer::Bullet));
    collider->setMask(static_cast<uint16>(ECollisionLayer::Enemy | ECollisionLayer::Wall));

    auto renderer = addComponent<Artifact::SpriteRenderer>();
    renderer->Width = 0.1f;
    renderer->Height = 0.02f;
    renderer->setTexture(Artifact::ResourceManager::getTexture("Textures/Bullet.png"));

    auto bulletComponent = addComponent<BulletComponent>();
    bulletComponent->Speed = 10.0f;
}
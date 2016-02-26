#include <BadEngine/IO/ResourceManager.h>
#include <BadEngine/Rendering/SpriteRenderer.h>
#include <BadEngine/Transform.h>
#include <BadEngine/Core/EntitySystem.h>
#include <BadEngine/Physics/BoxCollider2D.h>

#include "Enemy.h"
#include "../HealthComponent.h"

Enemy::Enemy(unsigned a_ID, BadEngine::EntitySystem& a_EntitySystem)
    : GameObject(a_ID, a_EntitySystem)
{
    auto renderer = addComponent<BadEngine::SpriteRenderer>();
    renderer->setTexture(BadEngine::ResourceManager::getTexture("Textures/Zombie textures/skeleton-move_0.png"));
    renderer->Width = 1.0f;
    renderer->Height = 1.0f;
    getComponent<BadEngine::Transform>()->setLocalPosition(glm::vec2(0.4f, 0.0f));

    auto health = addComponent<HealthComponent>();
    health->CurrentHealth = health->MaxHealth = 5;

    auto collider = addComponent<BadEngine::BoxCollider2D>();
    collider->enableTriggerState();
    collider->setDimensions(glm::vec2(1.0f, 1.0f));
}
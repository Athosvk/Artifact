#include <BadEngine/Physics/MovementComponent.h>
#include <BadEngine/Rendering/SpriteRenderer.h>
#include <BadEngine/IO/ResourceManager.h>
#include <BadEngine/Core/EntitySystem.h>

#include "Bullet.h"

Bullet::Bullet(unsigned a_ID, BadEngine::EntitySystem& a_EntitySystem)
    : GameObject(a_ID, a_EntitySystem)
{
    addComponent<BadEngine::MovementComponent>()->Speed = 0.25f;
    auto renderer = addComponent<BadEngine::SpriteRenderer>();
    renderer->setTexture(BadEngine::ResourceManager::getTexture("Textures/PNG/Bullet.png"));
    renderer->Width = 0.1f;
    renderer->Height = 0.1f;
}
#include <BadEngine/IO/ResourceManager.h>
#include <BadEngine/Rendering/SpriteRenderer.h>
#include <BadEngine/Transform.h>
#include <BadEngine/Core/EntitySystem.h>

#include "Enemy.h"

Enemy::Enemy(unsigned a_ID, BadEngine::EntitySystem& a_EntitySystem)
    : GameObject(a_ID, a_EntitySystem)
{
    auto renderer = addComponent<BadEngine::SpriteRenderer>();
    renderer->setTexture(BadEngine::ResourceManager::getTexture("Textures/Zombie textures/skeleton-move_0.png"));
    renderer->Width = 1;
    renderer->Height = 1;
    getComponent<BadEngine::Transform>()->setLocalPosition(glm::vec2(0.4f, 0.0f));
}
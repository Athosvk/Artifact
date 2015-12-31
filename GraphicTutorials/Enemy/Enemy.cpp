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
    renderer->Width = 100;
    renderer->Height = 100;
    getComponent<BadEngine::Transform>()->LocalPosition = glm::vec2(40.0f, 0.0f);
}
#include <BadEngine/Physics/BoxCollider2D.h>
#include <BadEngine/Rendering/SpriteRenderer.h>
#include <BadEngine/IO/ResourceManager.h>
#include <BadEngine/Core/EntitySystem.h>

#include "Ground.h"

Ground::Ground(unsigned a_ID, BadEngine::EntitySystem& a_EntitySystem)
    : GameObject(a_ID, a_EntitySystem)
{
    auto renderer = addComponent<BadEngine::SpriteRenderer>();
    renderer->Width = 2.0f;
    renderer->Height = 0.5f;
    renderer->setTexture(BadEngine::ResourceManager::getTexture("Textures/Box.png"));

    auto collider = addComponent<BadEngine::BoxCollider2D>();
    collider->setDimensions(glm::vec2(2.0f, 0.5f));
}

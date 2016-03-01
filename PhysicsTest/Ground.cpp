#include <Artifact/Physics/BoxCollider2D.h>
#include <Artifact/Rendering/SpriteRenderer.h>
#include <Artifact/IO/ResourceManager.h>
#include <Artifact/Core/EntitySystem.h>

#include "Ground.h"

Ground::Ground(unsigned a_ID, Artifact::EntitySystem& a_EntitySystem)
    : GameObject(a_ID, a_EntitySystem)
{
    auto renderer = addComponent<Artifact::SpriteRenderer>();
    renderer->Width = 8.0f;
    renderer->Height = 0.5f;
    renderer->setTexture(Artifact::ResourceManager::getTexture("Textures/Box.png"));

    auto collider = addComponent<Artifact::BoxCollider2D>();
    collider->setDimensions(glm::vec2(8.0f, 0.5f));
    //collider->enableTriggerState();
}

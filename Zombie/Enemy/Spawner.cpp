#include <Artifact/Core/EntitySystem.h>
#include <Artifact/Rendering/SpriteRenderer.h>
#include <Artifact/IO/ResourceManager.h>

#include "Spawner.h"
#include "SpawnerComponent.h"

Spawner::Spawner(unsigned a_ID, Artifact::EntitySystem& a_EntitySystem)
    : GameObject(a_ID, a_EntitySystem)
{
    addComponent<SpawnerComponent>();
    auto renderer = addComponent<Artifact::SpriteRenderer>();
    renderer->setTexture(Artifact::ResourceManager::getTexture("Textures/Grave_1.png"));
    renderer->Height = 1.0f;
    renderer->Width = 1.0f;
    renderer->Depth = -1.0f;
}

#include <Artifact/Core/EntitySystem.h>
#include <Artifact/Transform.h>

#include "SpawnerComponent.h"

SpawnerComponent::SpawnerComponent(Artifact::GameObject a_Entity)
    : Component(a_Entity)
{
}

glm::vec2 SpawnerComponent::getSpawnPosition() const
{
    return getComponent<Artifact::Transform>()->getPosition();
}

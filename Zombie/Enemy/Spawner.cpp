#include <Artifact/Core/EntitySystem.h>

#include "Spawner.h"
#include "SpawnerComponent.h"

Spawner::Spawner(unsigned a_ID, Artifact::EntitySystem& a_EntitySystem)
    : GameObject(a_ID, a_EntitySystem)
{
    addComponent<SpawnerComponent>();
}

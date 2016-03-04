#include <Artifact/Core/World.h>
#include <Artifact/Random.h>
#include <Artifact/Transform.h>

#include "SpawnerSystem.h"
#include "SpawnerComponent.h"
#include "Enemy.h"

const float SpawnerSystem::SpawnInterval = 3.5f;

SpawnerSystem::SpawnerSystem(Artifact::EntitySystem& a_EntitySystem, Artifact::MessagingSystem& a_MessagingSystem)
    : System(a_EntitySystem, a_MessagingSystem)
{
}

void SpawnerSystem::registerListeners()
{
    m_MessagingSystem.registerListener<Artifact::UpdateMessage>([this](const Artifact::Message* a_Message)
    {
        update(static_cast<const Artifact::UpdateMessage*>(a_Message)->getGameTime().getDeltaTime());
    });
}

void SpawnerSystem::update(double a_DeltaTime)
{
    auto spawners = m_EntitySystem.getComponentsOfType<SpawnerComponent>();
    m_TimeSinceSpawn += a_DeltaTime;
    while(m_TimeSinceSpawn >= SpawnInterval)
    {
        m_TimeSinceSpawn -= SpawnInterval;
        triggerSpawn(spawners);
    }
}

void SpawnerSystem::triggerSpawn(std::vector<SpawnerComponent*>& a_Spawners)
{
    auto spawnPosition = a_Spawners[Artifact::Random::range(0, a_Spawners.size() - 1)]->getSpawnPosition();
    auto spawnedEnemy = m_EntitySystem.createEntity<Enemy>();
    spawnedEnemy.getComponent<Artifact::Transform>()->setPosition(spawnPosition);
}

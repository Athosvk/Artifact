#pragma once
#include <Artifact/Core/System.h>

class SpawnerComponent;

class SpawnerSystem : public Artifact::System
{
private:
    static const float SpawnInterval;

    double m_TimeSinceSpawn = 0.0f;

public:
    SpawnerSystem(Artifact::EntitySystem& a_EntitySystem, Artifact::MessagingSystem& a_MessagingSystem);

    virtual void registerListeners() override;
private:
    void update(double a_DeltaTime);
    void triggerSpawn(std::vector<SpawnerComponent*>& a_Spawners);
};

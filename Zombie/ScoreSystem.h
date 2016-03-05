#pragma once
#include <Artifact/Core/System.h>

class ScoreComponent;
class HealthComponent;

class ScoreSystem : public Artifact::System
{
public:
    ScoreSystem(Artifact::EntitySystem& a_EntitySystem, Artifact::MessagingSystem& a_MessagingSystem);

    virtual void registerListeners() override;
private:
    void onScoreComponentAdd(ScoreComponent* a_ScoreComponent) const;
    void onEnemyDeath(HealthComponent* a_EnemyHealth) const;
};


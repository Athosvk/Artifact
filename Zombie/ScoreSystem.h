#pragma once
#include <BadEngine/Core/System.h>

class ScoreComponent;
class HealthComponent;

class ScoreSystem : public BadEngine::System
{
public:
    ScoreSystem(BadEngine::EntitySystem& a_EntitySystem, BadEngine::MessagingSystem& a_MessagingSystem);

    virtual void registerListeners() override;
private:
    void onScoreComponentAdd(ScoreComponent* a_ScoreComponent) const;
    void onEnemyDeath(HealthComponent* a_EnemyHealth) const;
};


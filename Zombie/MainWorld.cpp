#include <Artifact/Game.h>

#include "MainWorld.h"
#include "Player/PlayerInputSystem.h"
#include "Enemy/Enemy.h"
#include "Player/WeaponSystem.h"
#include "TimerSystem.h"
#include "Enemy/FollowSystem.h"
#include "BulletSystem.h"
#include "Enemy/AttackSystem.h"
#include "Enemy/ZombieBehaviourSystem.h"
#include "HealthComponent.h"
#include "GameOverScreen.h"
#include "Player/HUDSystem.h"
#include "ScoreSystem.h"
#include "Enemy/SpawnerSystem.h"
#include "Enemy/Spawner.h"

MainWorld::MainWorld(Artifact::GameTime& a_GameTime, Artifact::Game* a_CurrentGame)
    : World(a_GameTime, a_CurrentGame)
{
    addSystem<PlayerInputSystem>();
    addSystem<WeaponSystem>();
    addSystem<TimerSystem>();
    addSystem<FollowSystem>();
    addSystem<BulletSystem>();
    addSystem<AttackSystem>();
    addSystem<HUDSystem>();
    addSystem<ZombieBehaviourSystem>();
    addSystem<ScoreSystem>();
    addSystem<SpawnerSystem>();

    m_EntitySystem.createEntity<Enemy>();
    auto enemy2 = m_EntitySystem.createEntity<Enemy>();
    enemy2.getComponent<Artifact::Transform>()->setPosition(glm::vec2(0.5f, 1.0f));

    auto player = m_EntitySystem.createEntity<Player>();
    player.getComponent<HealthComponent>()->OnDeath += [this](const HealthComponent*)
    { 
        loadGameoverScreen(); 
    };

    auto spawner = m_EntitySystem.createEntity<Spawner>();
    spawner.getComponent<Artifact::Transform>()->setPosition(glm::vec2(3.0f, 3.0f));
}

void MainWorld::loadGameoverScreen() const
{
    m_CurrentGame->loadWorld<GameOverScreen>();
}

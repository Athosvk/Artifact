#include <BadEngine/Game.h>

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

MainWorld::MainWorld(BadEngine::GameTime& a_GameTime, BadEngine::Game* a_CurrentGame)
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
    m_EntitySystem.createEntity<Enemy>();
    auto enemy2 = m_EntitySystem.createEntity<Enemy>();
    enemy2.getComponent<BadEngine::Transform>()->setPosition(glm::vec2(0.5f, 1.0f));

    auto player = m_EntitySystem.createEntity<Player>();
    player.getComponent<HealthComponent>()->OnDeath += [this](const HealthComponent*) 
    { 
        loadGameoverScreen(); 
    };
}

void MainWorld::loadGameoverScreen() const
{
    m_CurrentGame->loadWorld<GameOverScreen>();
}

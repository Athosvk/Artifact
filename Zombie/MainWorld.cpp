#include "MainWorld.h"
#include "Player/PlayerInputSystem.h"
#include "Enemy/Enemy.h"
#include "Player/WeaponSystem.h"
#include "TimerSystem.h"
#include "HealthSystem.h"
#include "Enemy/FollowSystem.h"

MainWorld::MainWorld(BadEngine::GameTime& a_GameTime)
    : World(a_GameTime)
{
    addSystem<PlayerInputSystem>();
    addSystem<WeaponSystem>();
    addSystem<TimerSystem>();
    addSystem<HealthSystem>();
    addSystem<FollowSystem>();
    m_EntitySystem.createEntity<Enemy>();
    m_EntitySystem.createEntity<Player>();
}
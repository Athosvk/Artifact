#include "MainWorld.h"
#include "Player/PlayerInputSystem.h"
#include "Enemy/Enemy.h"
#include "Player/WeaponSystem.h"
#include "TimerSystem.h"
#include "Enemy/FollowSystem.h"
#include "BulletSystem.h"
#include "Enemy/AttackSystem.h"
#include "Enemy/ZombieBehaviourSystem.h"

MainWorld::MainWorld(BadEngine::GameTime& a_GameTime)
    : World(a_GameTime)
{
    addSystem<PlayerInputSystem>();
    addSystem<WeaponSystem>();
    addSystem<TimerSystem>();
    addSystem<FollowSystem>();
    addSystem<BulletSystem>();
    addSystem<AttackSystem>();
    addSystem<ZombieBehaviourSystem>();
    m_EntitySystem.createEntity<Enemy>();
    auto enemy2 = m_EntitySystem.createEntity<Enemy>();
    enemy2.getComponent<BadEngine::Transform>()->setPosition(glm::vec2(0.5f, 1.0f));
    m_EntitySystem.createEntity<Player>();
}
#include "MainWorld.h"
#include "Player/PlayerInputSystem.h"
#include "Enemy/Enemy.h"
#include "Player/WeaponSystem.h"
#include "TimerSystem.h"

MainWorld::MainWorld(const BadEngine::Window& a_Window, BadEngine::GameTime& a_GameTime)
    : World(a_Window, a_GameTime)
{
    addSystem<PlayerInputSystem>();
    addSystem<WeaponSystem>();
    addSystem<TimerSystem>();
    m_EntitySystem.createEntity<Enemy>();
    m_EntitySystem.createEntity<Player>();
}
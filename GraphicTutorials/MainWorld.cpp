#include "MainWorld.h"
#include "Player/PlayerInputSystem.h"
#include "Enemy/Enemy.h"

MainWorld::MainWorld(const BadEngine::Window& a_Window)
    : World(a_Window),
    m_Player(m_EntitySystem)
{
    addSystem<PlayerInputSystem>();
    m_EntitySystem.createEntity<Enemy>();
}
#include <BadEngine/Transform.h>
#include <BadEngine/GameTime.h>

#include "PhysicsTestWorld.h"
#include "Player.h"
#include "PlayerInputSystem.h"
#include "Ground.h"
#include "Box.h"

PhysicsTestWorld::PhysicsTestWorld(BadEngine::Window& a_Window, BadEngine::GameTime& a_GameTime)
    : World(a_Window, a_GameTime)
{
    addSystem<PlayerInputSystem>();
    m_EntitySystem.createEntity<Player>();
    m_EntitySystem.createEntity<Ground>();
    for(int i = 0; i < 5; i++)
    {
        Box box = m_EntitySystem.createEntity<Box>();
        box.getComponent<BadEngine::Transform>()->setPosition(glm::vec2(i * 1- 1.5f, -1));
    }
}

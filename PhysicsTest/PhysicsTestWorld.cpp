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
    auto ground = m_EntitySystem.createEntity<Ground>();
    ground.getComponent<BadEngine::Transform>()->setPosition(glm::vec2(0.0f, -2.0f));
    for(int j = 0; j < 27; j++)
    {
        for(int i = 0; i < 50; i++)
        {
            Box box = m_EntitySystem.createEntity<Box>();
            auto transform = box.getComponent<BadEngine::Transform>();
            transform->setPosition(glm::vec2(i * 0.3f - 1.5f, 0.3f * j));
        }
    }
}

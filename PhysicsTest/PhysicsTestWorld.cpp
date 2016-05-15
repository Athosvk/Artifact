#include <Artifact/Transform.h>
#include <Artifact/GameTime.h>

#include "PhysicsTestWorld.h"
#include "Player.h"
#include "PlayerInputSystem.h"
#include "Ground.h"
#include "Box.h"

PhysicsTestWorld::PhysicsTestWorld(Artifact::GameTime& a_GameTime, Artifact::Game* a_Game)
    : World(a_GameTime, a_Game)
{
    addSystem<PlayerInputSystem>();
    m_EntitySystem.createEntity<Player>();
    auto ground = m_EntitySystem.createEntity<Ground>();
    ground.getComponent<Artifact::Transform>()->setPosition(glm::vec2(0.0f, -2.0f));

    //for(int j = 0; j < 27; j++)
    //{
    //    for(int i = 0; i < 50; i++)
    //    {
    //        Box box = m_EntitySystem.createEntity<Box>();
    //        auto transform = box.getComponent<Artifact::Transform>();
    //        transform->setPosition(glm::vec2(i * 0.3f - 1.5f, 0.3f * j));
    //    }
    //}
}

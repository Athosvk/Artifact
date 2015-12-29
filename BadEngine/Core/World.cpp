#include "World.h"
#include "Message.h"
#include "System.h"
#include "../Rendering/RenderSystem.h"

namespace BadEngine
{
    World::World()
    {
        addSystem<SpriteRenderSystem>();
    }

    void World::update()
    {
        broadcast<Message>(EMessageType::Update);
        broadcast<Message>(EMessageType::Render);
    }

    void World::fixedUpdate()
    {
        broadcast<Message>(EMessageType::FixedUpdate);
    }
}
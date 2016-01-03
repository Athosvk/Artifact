#include <iostream>

#include "World.h"
#include "../Rendering/SpriteRenderSystem.h"
#include "../Rendering/RenderMessage.h"
#include "../Physics/MovementSystem.h"

namespace BadEngine
{
    UpdateMessage::UpdateMessage(const GameTime& a_GameTime)
        : m_GameTime(a_GameTime)
    {
    }

    const GameTime& UpdateMessage::getGameTime()
    {
        return m_GameTime;
    }

    World::World(const Window& a_Window)
        : m_Camera(a_Window)
    {
        addDefaultSystems();
    }

    void* World::operator new(std::size_t a_Size)
    {
        return _aligned_malloc(a_Size, 16);
    }

    void World::operator delete(void* a_Pointer)
    {
        _aligned_free(a_Pointer);
    }

    void World::addDefaultSystems()
    {
        addSystem<SpriteRenderSystem>();
        addSystem<MovementSystem>();
    }

    void World::update()
    {
        broadcast<HandleInputMessage>();
        broadcast<RenderMessage>(&m_Camera.getTransform());
        broadcast<UpdateMessage>(m_GameTime);
        m_GameTime.update();
    }

    void World::fixedUpdate()
    {
        broadcast<FixedUpdateMessage>();
    }
}
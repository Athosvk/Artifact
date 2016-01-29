#include "World.h"
#include "../Rendering/SpriteRenderSystem.h"
#include "../Rendering/RenderMessage.h"
#include "../Physics/MovementSystem.h"
#include "../Physics/PhysicsSystem.h"
#include "../StopWatch.h"

namespace BadEngine
{
    UpdateMessage::UpdateMessage(const GameTime& a_GameTime)
        : m_GameTime(a_GameTime)
    {
    }

    World::World(const Window& a_Window, GameTime& a_GameTime)
        : m_Camera(a_Window),
        m_EntitySystem(m_MessagingSystem),
        m_GameTime(a_GameTime)
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
        addSystem<PhysicsSystem>();
    }

    void World::update()
    {
        broadcast<HandleInputMessage>();
        broadcast<UpdateMessage>(m_GameTime);
        broadcast<RenderMessage>(&m_Camera.getTransform());
        m_GameTime.update();
    }

    void World::fixedUpdate()
    {
        broadcast<FixedUpdateMessage>();
    }
}
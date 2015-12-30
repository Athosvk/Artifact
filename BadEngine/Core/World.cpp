#include "World.h"
#include "Message.h"
#include "../Rendering/SpriteRenderSystem.h"
#include "../Rendering/RenderMessage.h"
#include "../Physics/MovementSystem.h"

namespace BadEngine
{
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
        broadcast<Message>(EMessageType::HandleInput);
        broadcast<Message>(EMessageType::Update);
        broadcast<RenderMessage>(&m_Camera.getTransform());
    }

    void World::fixedUpdate()
    {
        broadcast<Message>(EMessageType::FixedUpdate);
    }
}
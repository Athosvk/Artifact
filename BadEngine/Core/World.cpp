#include "World.h"
#include "../Rendering/SpriteRenderSystem.h"
#include "../Rendering/RenderMessage.h"
#include "../Physics/MovementSystem.h"
#include "../Physics/PhysicsSystem.h"
#include "../Input/InputSystem.h"

namespace BadEngine
{
    UpdateMessage::UpdateMessage(const GameTime& a_GameTime)
        : m_GameTime(a_GameTime)
    {
    }

    const GameTime& UpdateMessage::getGameTime() const
    {
        return m_GameTime;
    }

    ProcessEventsMessage::ProcessEventsMessage(const std::vector<SDL_Event>& a_Events)
        : m_Events(a_Events)
    {
    }

    const std::vector<SDL_Event>& ProcessEventsMessage::getEvents() const
    {
        return m_Events;
    }

    World::World(GameTime& a_GameTime)
        : m_EntitySystem(m_MessagingSystem),
        m_GameTime(a_GameTime)
    {
        addDefaultSystems();
    }

    void World::addDefaultSystems()
    {
        auto mainCamera = m_EntitySystem.createEntity();
        broadcast<OnCameraChangedMessage>(mainCamera.addComponent<Camera2D>());

        addSystem<InputSystem>();
        addSystem<SpriteRenderSystem>();
        addSystem<MovementSystem>();
        addSystem<PhysicsSystem>();
    }

    void World::update()
    {
        broadcast<UpdateMessage>(m_GameTime);
        broadcast<RenderMessage>();
        m_GameTime.update();
    }

    void World::fixedUpdate()
    {
        broadcast<FixedUpdateMessage>();
    }

    void World::processEvents(std::vector<SDL_Event>& a_Events)
    {
        broadcast<ProcessEventsMessage>(a_Events);
    }
}
#include "World.h"
#include "../Rendering/SpriteRenderSystem.h"
#include "../Rendering/RenderMessage.h"
#include "../Physics/PhysicsSystem.h"
#include "../Input/InputSystem.h"
#include "../Rendering/UIRenderingSystem.h"
#include "../Audio/AudioSystem.h"

namespace Artifact
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

    World::World(GameTime& a_GameTime, Game* a_CurrentGame)
        : m_EntitySystem(m_MessagingSystem),
        m_GameTime(a_GameTime),
        m_CurrentGame(a_CurrentGame)
    {
        addDefaultSystems();
    }

    void World::addDefaultSystems()
    {
        auto mainCamera = m_EntitySystem.createEntity();
        broadcast<OnCameraChangedMessage>(mainCamera.addComponent<Camera2D>());

        addSystem<InputSystem>();
        addSystem<SpriteRenderSystem>();
        addSystem<PhysicsSystem>();
        addSystem<UIRenderingSystem>();
        addSystem<AudioSystem>();
    }

    void World::awake()
    {
        m_MessagingSystem.broadcast<AwakeMessage>();
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
        broadcast<PhysicsUpdateMessage>();
    }

    void World::processEvents(std::vector<SDL_Event>& a_Events)
    {
        broadcast<ProcessEventsMessage>(a_Events);
    }
}
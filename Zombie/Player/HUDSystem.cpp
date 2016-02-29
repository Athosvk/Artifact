#include <BadEngine/Rendering/RenderMessage.h>
#include <BadEngine/Core/EntitySystem.h>

#include "PlayerComponent.h"
#include "../HealthComponent.h"

#include "HUDSystem.h"

HUDSystem::HUDSystem(BadEngine::EntitySystem& a_EntitySystem, BadEngine::MessagingSystem& a_MessagingSystem)
    : System(a_EntitySystem, a_MessagingSystem),
    m_HealthBar(m_EntitySystem)
{
}

void HUDSystem::registerListeners()
{
    m_MessagingSystem.registerListener<BadEngine::RenderMessage>([this](const BadEngine::Message*)
    {
        renderHUDComponents();
    });
}

void HUDSystem::renderHUDComponents()
{
    m_HealthBar.render(getCurrentPlayer()->getComponent<HealthComponent>());
}

PlayerComponent* HUDSystem::getCurrentPlayer() const
{
    return m_EntitySystem.getComponentsOfType<PlayerComponent>()[0];
}

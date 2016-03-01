#include <BadEngine/Rendering/RenderMessage.h>
#include <BadEngine/Core/EntitySystem.h>
#include <BadEngine/Rendering/TextComponent.h>
#include <BadEngine/IO/ResourceManager.h>

#include "PlayerComponent.h"
#include "../HealthComponent.h"

#include "HUDSystem.h"

HUDSystem::HUDSystem(BadEngine::EntitySystem& a_EntitySystem, BadEngine::MessagingSystem& a_MessagingSystem)
    : System(a_EntitySystem, a_MessagingSystem),
    m_HealthBar(m_EntitySystem),
    m_Text(m_EntitySystem.createEntity())
{
    auto text = m_Text.addComponent<BadEngine::TextComponent>();
    text->Text = "AAAA";
    text->Depth = 10.0f;
    text->Font = BadEngine::ResourceManager::getFont("Fonts/BasicFont.ttf");
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

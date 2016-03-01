#include <Artifact/Rendering/RenderMessage.h>
#include <Artifact/Core/EntitySystem.h>
#include <Artifact/Rendering/TextComponent.h>
#include <Artifact/IO/ResourceManager.h>

#include "PlayerComponent.h"
#include "../HealthComponent.h"

#include "HUDSystem.h"

HUDSystem::HUDSystem(Artifact::EntitySystem& a_EntitySystem, Artifact::MessagingSystem& a_MessagingSystem)
    : System(a_EntitySystem, a_MessagingSystem),
    m_HealthBar(m_EntitySystem),
    m_Text(m_EntitySystem.createEntity())
{
    auto text = m_Text.addComponent<Artifact::TextComponent>();
    text->Text = "AAAA";
    text->Depth = 10.0f;
    text->Font = Artifact::ResourceManager::getFont("Fonts/BasicFont.ttf");
}

void HUDSystem::registerListeners()
{
    m_MessagingSystem.registerListener<Artifact::RenderMessage>([this](const Artifact::Message*)
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

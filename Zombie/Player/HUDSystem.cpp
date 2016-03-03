#include <Artifact/Core/World.h>
#include <Artifact/Core/EntitySystem.h>
#include <Artifact/Rendering/TextComponent.h>
#include <Artifact/IO/ResourceManager.h>
#include <Artifact/Transform.h>

#include "PlayerComponent.h"
#include "../HealthComponent.h"
#include "PlayerScoreComponent.h"

#include "HUDSystem.h"

HUDSystem::HUDSystem(Artifact::EntitySystem& a_EntitySystem, Artifact::MessagingSystem& a_MessagingSystem)
    : System(a_EntitySystem, a_MessagingSystem),
    m_HealthBar(m_EntitySystem, glm::vec2(3.0f, 3.4f))
{
    m_ScoreDisplay = m_EntitySystem.createEntity().addComponent<Artifact::TextComponent>();
    m_ScoreDisplay->Text = "Score: ";
    m_ScoreDisplay->Font = Artifact::ResourceManager::getFont("Fonts/BasicFont.ttf");
    m_ScoreDisplay->getComponent<Artifact::Transform>()->setPosition(glm::vec2(-4.9f, 3.4f));
    m_ScoreDisplay->Justification = Artifact::EJustification::Left;
    m_ScoreDisplay->Scaling = 0.4f;
    m_ScoreDisplay->Depth = 100.0f;
}

void HUDSystem::registerListeners()
{
    m_MessagingSystem.registerListener<Artifact::UpdateMessage>([this](const Artifact::Message*)
    {
        updateHUDComponents();
    });
}

void HUDSystem::updateHUDComponents()
{
    m_HealthBar.update(getCurrentPlayer()->getComponent<HealthComponent>());
    m_ScoreDisplay->Text = "Score: " + std::to_string(getCurrentPlayer()->
        getComponent<PlayerScoreComponent>()->CurrentScore);
}

PlayerComponent* HUDSystem::getCurrentPlayer() const
{
    return m_EntitySystem.getComponentsOfType<PlayerComponent>()[0];
}

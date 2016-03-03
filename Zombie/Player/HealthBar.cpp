#include <Artifact/Rendering/SpriteRenderer.h>
#include <Artifact/Core/EntitySystem.h>
#include <Artifact/Transform.h>
#include <Artifact/IO/ResourceManager.h>

#include "PlayerComponent.h"
#include "../HealthComponent.h"

#include "HealthBar.h"

const float HealthBar::MaxWidth = 2.0f;
const float HealthBar::Height = 0.3f;
const glm::vec2 HealthBar::BackgroundOffset = glm::vec2(-0.05f, -0.05f);

HealthBar::HealthBar(Artifact::EntitySystem& a_EntitySystem, glm::vec2 a_Position)
    : m_Position(a_Position)
{
    m_HealthRenderer = a_EntitySystem.createEntity().addComponent<Artifact::SpriteRenderer>();
    initialiseHealthbar();

    auto backgroundRenderer = a_EntitySystem.createEntity().addComponent<Artifact::SpriteRenderer>();

    backgroundRenderer->setTexture(Artifact::ResourceManager::getTexture("Textures/Healthbar_background.png"));
    backgroundRenderer->getComponent<Artifact::Transform>()->setPosition(a_Position + BackgroundOffset);
    backgroundRenderer->Width = MaxWidth + 0.1f;
    backgroundRenderer->Height = Height + 0.1f;
    backgroundRenderer->Depth = 100.0f;
    backgroundRenderer->Pivot = glm::vec2(0.0f, 0.0f);
}

void HealthBar::update(HealthComponent* a_Health)
{
    m_HealthRenderer->Width = (a_Health->getCurrentHealth() /
        static_cast<float>(a_Health->MaxHealth)) * MaxWidth;
}

void HealthBar::initialiseHealthbar()
{
    m_HealthRenderer->getComponent<Artifact::Transform>()->setPosition(m_Position);
    m_HealthRenderer->setTexture(Artifact::ResourceManager::getTexture("Textures/Healthbar.png"));
    m_HealthRenderer->Width = MaxWidth;
    m_HealthRenderer->Height = Height;
    m_HealthRenderer->Pivot = glm::vec2(0.0f, 0.0f);
    m_HealthRenderer->Depth = 101.0f;
}
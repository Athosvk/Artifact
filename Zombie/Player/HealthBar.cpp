#include <BadEngine/Rendering/SpriteRenderer.h>
#include <BadEngine/Core/EntitySystem.h>
#include <BadEngine/Transform.h>
#include <BadEngine/IO/ResourceManager.h>

#include "PlayerComponent.h"
#include "../HealthComponent.h"

#include "HealthBar.h"

const float HealthBar::MaxWidth = 2.0f;
const float HealthBar::Height = 0.3f;

HealthBar::HealthBar(BadEngine::EntitySystem& a_EntitySystem)
{
    m_HealthRenderer = a_EntitySystem.createEntity().addComponent<BadEngine::SpriteRenderer>();
    initialiseHealthbar();

    auto backgroundRenderer = a_EntitySystem.createEntity().addComponent<BadEngine::SpriteRenderer>();

    backgroundRenderer->setTexture(BadEngine::ResourceManager::getTexture("Textures/Healthbar_background.png"));
    backgroundRenderer->getComponent<BadEngine::Transform>()->setPosition(glm::vec2(1.5f, 2.5f));
    backgroundRenderer->Width = MaxWidth;
    backgroundRenderer->Height = Height;
    backgroundRenderer->Depth = -1;
    backgroundRenderer->Pivot = glm::vec2(0.0f, 0.0f);
}

void HealthBar::render(HealthComponent* a_Health)
{
    m_HealthRenderer->Width = (a_Health->getCurrentHealth() /
        static_cast<float>(a_Health->MaxHealth)) * MaxWidth;
}

void HealthBar::initialiseHealthbar()
{
    m_HealthRenderer->getComponent<BadEngine::Transform>()->setPosition(glm::vec2(1.5f, 2.5f));
    m_HealthRenderer->setTexture(BadEngine::ResourceManager::getTexture("Textures/Healthbar.png"));
    m_HealthRenderer->Width = MaxWidth;
    m_HealthRenderer->Height = Height;
    m_HealthRenderer->Pivot = glm::vec2(0.0f, 0.0f);
}
#include <Artifact/Rendering/TextComponent.h>
#include <Artifact/IO/ResourceManager.h>
#include <Artifact/Transform.h>

#include "GameOverScreen.h"

GameOverScreen::GameOverScreen(Artifact::GameTime& a_GameTime, Artifact::Game* a_CurrentGame, unsigned a_Score)
    : World(a_GameTime, a_CurrentGame)
{
    auto font = Artifact::ResourceManager::getFont("Fonts/BasicFont.ttf");

    auto text = m_EntitySystem.createEntity().addComponent<Artifact::TextComponent>();
    text->Text = "GAME OVER";
    text->Color = Artifact::Color(128, 0, 0);
    text->Font = font;

    auto score = m_EntitySystem.createEntity().addComponent<Artifact::TextComponent>();
    score->Text = "Score: " + std::to_string(a_Score);
    score->Color = Artifact::Color(128, 0, 0);
    score->Font = font;
    score->Scaling = 0.3f;
    score->getComponent<Artifact::Transform>()->setPosition(glm::vec2(-3.5f, -3.0f));
}

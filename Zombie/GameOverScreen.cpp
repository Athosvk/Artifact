#include <Artifact/Rendering/TextComponent.h>
#include <Artifact/IO/ResourceManager.h>

#include "GameOverScreen.h"

GameOverScreen::GameOverScreen(Artifact::GameTime& a_GameTime, Artifact::Game* a_CurrentGame)
    : World(a_GameTime, a_CurrentGame)
{
    auto text = m_EntitySystem.createEntity().addComponent<Artifact::TextComponent>();
    text->Text = "GAME OVER";
    text->Color = Artifact::Color(128, 0, 0);
    text->Font = Artifact::ResourceManager::getFont("Fonts/BasicFont.ttf");
    text->Scaling = 1.0f;
}

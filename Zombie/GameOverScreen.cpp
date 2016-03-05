#include <Artifact/Rendering/TextComponent.h>
#include <Artifact/IO/ResourceManager.h>
#include <Artifact/Transform.h>
#include <Artifact/Input/Keyboard.h>
#include <Artifact/Game.h>
#include <Artifact/Input/InputSystem.h>
#include <Artifact/Rendering/SpriteRenderer.h>

#include "GameOverScreen.h"
#include "MainWorld.h"

GameOverScreen::GameOverScreen(Artifact::GameTime& a_GameTime, Artifact::Game* a_CurrentGame, unsigned a_Score)
    : World(a_GameTime, a_CurrentGame)
{
    auto font = Artifact::ResourceManager::getFont("Fonts/BasicFont.ttf");

    auto gameOverText = m_EntitySystem.createEntity().addComponent<Artifact::TextComponent>();
    gameOverText->Text = "GAME OVER";
    gameOverText->Color = Artifact::Color(128, 0, 0);
    gameOverText->Font = font;

    auto score = m_EntitySystem.createEntity().addComponent<Artifact::TextComponent>();
    score->Text = "Score: " + std::to_string(a_Score);
    score->Color = Artifact::Color(128, 0, 0);
    score->Font = font;
    score->Scaling = 0.3f;
    score->getComponent<Artifact::Transform>()->setPosition(glm::vec2(-3.5f, -3.0f));

    auto replayText = m_EntitySystem.createEntity().addComponent<Artifact::TextComponent>();
    replayText->Font = font;
    replayText->Text = "Press enter to play again";
    replayText->Scaling = 0.45f;
    replayText->Color = Artifact::Color(175, 0, 0);
    replayText->getComponent<Artifact::Transform>()->setPosition(glm::vec2(0.0f, -1.0f));

    auto background = m_EntitySystem.createEntity().addComponent<Artifact::SpriteRenderer>();
    background->Height = 9.0f;
    background->Width = 11.0f;
    background->Depth = -10.0f;
    background->setTexture(Artifact::ResourceManager::getTexture("Textures/Gameover_background.png"));

    m_MessagingSystem.registerListener<Artifact::HandleInputMessage>([this](const Artifact::Message* a_Message)
    {
        handleInput();
    });
}

void GameOverScreen::handleInput()
{
    if(Artifact::Keyboard::isPressed(Artifact::KeyCode::Return))
    {
        m_CurrentGame->loadWorld<MainWorld>();
    }
}

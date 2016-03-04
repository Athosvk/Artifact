#include <Artifact/Rendering/SpriteRenderer.h>
#include <Artifact/IO/ResourceManager.h>
#include <Artifact/Audio/AudioSource.h>
#include <Artifact/Input/InputSystem.h>
#include <Artifact/Game.h>

#include "StartScreen.h"
#include "../MainWorld.h"

StartScreen::StartScreen(Artifact::GameTime& a_GameTime, Artifact::Game* a_CurrentGame)
    : World(a_GameTime, a_CurrentGame)
{
    auto background = m_EntitySystem.createEntity().addComponent<Artifact::SpriteRenderer>();
    background->setTexture(Artifact::ResourceManager::getTexture("Textures/Gameover_background.png"));
    m_BackgroundMusic = background->addComponent<Artifact::AudioSource>();
    m_BackgroundMusic->enableLooping();

    m_BackgroundMusic->Sound = Artifact::ResourceManager::getSound("Sounds/intro.mp3");
    m_BackgroundMusic->Volume = 0.15f;
    m_BackgroundMusic->play();

    m_MessagingSystem.registerListener<Artifact::HandleInputMessage>([this](const Artifact::Message*)
    {
        handleInput();
    });
}

StartScreen::~StartScreen()
{
    m_BackgroundMusic->stop();
}

void StartScreen::handleInput()
{
    if(Artifact::Keyboard::isPressed(Artifact::KeyCode::Return))
    m_CurrentGame->loadWorld<MainWorld>();
}

#include <Artifact/Rendering/SpriteRenderer.h>
#include <Artifact/IO/ResourceManager.h>
#include <Artifact/Audio/AudioSource.h>
#include <Artifact/Input/InputSystem.h>
#include <Artifact/Game.h>
#include <Artifact/Rendering/TextComponent.h>
#include <Artifact/Transform.h>

#include "StartScreen.h"
#include "../MainWorld.h"
#include "OptionComponent.h"
#include "../Menu/OptionSelectSystem.h"

StartScreen::StartScreen(Artifact::GameTime& a_GameTime, Artifact::Game* a_CurrentGame)
    : World(a_GameTime, a_CurrentGame),
    m_ControlsPopup(m_EntitySystem.createEntity())
{
    auto background = m_EntitySystem.createEntity().addComponent<Artifact::SpriteRenderer>();
    background->setTexture(Artifact::ResourceManager::getTexture("Textures/Gameover_background.png"));
    background->Width = 11.0f;
    background->Height = 9.0f;

    m_BackgroundMusic = background->addComponent<Artifact::AudioSource>();
    m_BackgroundMusic->enableLooping();

    m_BackgroundMusic->Sound = Artifact::ResourceManager::getSound("Sounds/intro.mp3");
    m_BackgroundMusic->Volume = 0.15f;
    m_BackgroundMusic->play();


    m_MessagingSystem.registerListener<Artifact::HandleInputMessage>([this](const Artifact::Message*)
    {
        handleInput();
    });
    initializeOptions();
    initializePopup();
    addSystem<OptionSelectSystem>();
}

StartScreen::~StartScreen()
{
    m_BackgroundMusic->stop();
}

void StartScreen::handleInput()
{

}

void StartScreen::initializeOptions()
{
    const auto Scaling = 0.35f;
    const auto DefaultColor = Artifact::Color(0.5f, 0.5f, 0.5f);
    const auto SelectedColor = Artifact::Color(0.9f, 0.9f, 0.9f);

    auto startGameOption = m_EntitySystem.createEntity().addComponent<OptionComponent>();
    startGameOption->getComponent<Artifact::Transform>()->setPosition(glm::vec2(0.0f, 0.5f));
    auto startGameText = startGameOption->addComponent<Artifact::TextComponent>();

    startGameText->Text = "Start game";
    startGameText->Color = DefaultColor;
    startGameText->Font = Artifact::ResourceManager::getFont("Fonts/BasicFont.ttf");
    startGameText->Scaling = Scaling;

    startGameOption->OnPress += [this]()
    {
        m_CurrentGame->loadWorld<MainWorld>();
    };

    startGameOption->Index = 0;
    startGameOption->OnSelect += [startGameText, SelectedColor]()
    {
        startGameText->Color = SelectedColor;
    };

    startGameOption->OnDeselect += [startGameText, DefaultColor]()
    {
        startGameText->Color = DefaultColor;
    };

    auto showControlsOption = m_EntitySystem.createEntity().addComponent<OptionComponent>();
    showControlsOption->getComponent<Artifact::Transform>()->setPosition(glm::vec2(0.0f, -0.5f));

    auto showControlsText = showControlsOption->addComponent<Artifact::TextComponent>();

    showControlsText->Text = "Controls";
    showControlsText->Color = DefaultColor;
    showControlsText->Font = Artifact::ResourceManager::getFont("Fonts/BasicFont.ttf");
    showControlsText->Scaling = Scaling;

    showControlsOption->OnPress += [this]()
    {
        if(!m_ControlsPopup.isActive())
        {
            m_ControlsPopup.activate();
        }
        else
        {
            m_ControlsPopup.deactivate();
        }
    };

    showControlsOption->Index = 1;
    showControlsOption->OnSelect += [showControlsText, SelectedColor]()
    {
        showControlsText->Color = SelectedColor;
    };

    showControlsOption->OnDeselect += [this, showControlsText, DefaultColor]()
    {
        showControlsText->Color = DefaultColor;
        if(m_ControlsPopup.isActive())
        {
            m_ControlsPopup.deactivate();
        }
    };
}

void StartScreen::initializePopup()
{
    auto controlsTexture = m_ControlsPopup.addComponent<Artifact::SpriteRenderer>();
    controlsTexture->setTexture(Artifact::ResourceManager::getTexture("Textures/Controls.png"));
    controlsTexture->Width = 4.0f;
    controlsTexture->Height = 2.0f;
    controlsTexture->Depth = 1.0f;
    controlsTexture->getComponent<Artifact::Transform>()->setPosition(glm::vec2(0.0f, -2.0f));
    m_ControlsPopup.deactivate();
}
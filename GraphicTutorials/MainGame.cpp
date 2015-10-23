#include <iostream>
#include <glm/glm.hpp>

#include <BadEngine/ImageLoader.h>
#include <BadEngine/Color.h>
#include <BadEngine/Keyboard.h>
#include <BadEngine/MathHelper.h>
#include <BadEngine/GLTexture.h>
#include <BadEngine/Camera2D.h>

#include "TestSprite.h"
#include "MainGame.h"
#include <BadEngine/ResourceManager.h>

MainGame::MainGame() : Game(1024, 768, 0, "GameEngine"),
    m_SpriteBatch(&m_Camera)
{
    setBackgroundColor(BadEngine::Color(0, 45, 75, 0));
    m_Sprites.push_back(new BadEngine::Sprite(glm::vec2(512.0f - 50.0f, 50.0f), "Textures/PNG/CharacterRight_Walk1.png", 20, 20));
    m_Sprites.push_back(new BadEngine::Sprite(glm::vec2(512.0f - 50.0f, 384.0f - 50.0f), "Textures/PNG/CharacterRight_Walk1.png", 500, 500));
    m_Sprites.push_back(new TestSprite(glm::vec2(-25.0f, -25.0f), 125.0f, 125.0f));
    printf(" *** OpenGL version: %s *** \n You need at least version %5.2f to run the game. \n", 
           reinterpret_cast<const char*>(glGetString(GL_VERSION)), m_OpenGLVersion);
    m_Camera.setZoomFactor(2.0f);
}

MainGame::~MainGame()
{
    for(unsigned int i = 0; i < m_Sprites.size(); ++i)
    {
        delete m_Sprites[i];
    }
}

void MainGame::draw()
{
    Game::draw();

    m_SpriteBatch.begin();

    BadEngine::Rectangle rectangle2(glm::vec2(512.0f - 50.0f, 384.0f - 50.0f), 15, 15);
    BadEngine::Rectangle uvRectangle2(glm::vec2(0, 0), 1, 1);
    m_SpriteBatch.draw(BadEngine::ResourceManager::getTexture("Textures/PNG/CharacterRight_Walk1.png"), rectangle2, uvRectangle2);
   
    BadEngine::Rectangle rectangle(glm::vec2(15, 15), 250, 250);
    BadEngine::Rectangle uvRectangle(glm::vec2(0, 0), 4, 4);
    m_SpriteBatch.draw(BadEngine::ResourceManager::getTexture("Textures/PNG/CharacterRight_Walk1.png"), rectangle, uvRectangle, BadEngine::Color::White);

    rectangle = BadEngine::Rectangle(glm::vec2(-25.0f, -25.0f), 125, 125);
    uvRectangle = BadEngine::Rectangle(glm::vec2(0, 0), 1, 1);
   m_SpriteBatch.draw(BadEngine::ResourceManager::getTexture("Textures/PNG/CharacterRight_Walk1.png"), rectangle, uvRectangle);

    m_SpriteBatch.end();
    for(auto sprite : m_Sprites)
    {
        sprite->draw(&m_Camera);
    }
}

void MainGame::update()
{
    Game::update();

    if(fmod(m_GameTime.getCurrentTime(), 0.5f) >= 0.48f)
    {
        std::cout << "FPS: " << 1 / m_GameTime.getAverageDeltaTime() << std::endl;
    }

    auto targetPosition = m_Camera.getPosition();
    auto zoomFactor = m_Camera.getZoomFactor();
    auto rotation = m_Camera.getRotation();
    if(BadEngine::Keyboard::isDown(BadEngine::KeyCode::Down))
    {
        targetPosition.y = BadEngine::MathHelper::clamp(targetPosition.y + 5, 0, 924);
    }
    if(BadEngine::Keyboard::isDown(BadEngine::KeyCode::Left))
    {
        targetPosition.x = BadEngine::MathHelper::clamp(targetPosition.x - 5, 0, 924);
    }
    if(BadEngine::Keyboard::isDown(BadEngine::KeyCode::Right))
    {
        targetPosition.x = BadEngine::MathHelper::clamp(targetPosition.x + 5, 0, 668);
    }
    if(BadEngine::Keyboard::isDown(BadEngine::KeyCode::Up))
    {
        targetPosition.y = BadEngine::MathHelper::clamp(targetPosition.y - 5, 0, 668);
    }
    if(BadEngine::Keyboard::isDown(BadEngine::KeyCode::W))
    {
        zoomFactor = BadEngine::MathHelper::clamp(zoomFactor + 0.05f, 0.01f, 2.0f);
    }
    if(BadEngine::Keyboard::isDown(BadEngine::KeyCode::S))
    {
        zoomFactor = BadEngine::MathHelper::clamp(zoomFactor - 0.05f, 0.01f, 2.0f);
    }
    if(BadEngine::Keyboard::isDown(BadEngine::KeyCode::Q))
    {
        rotation += 0.05f;
    }
    if(BadEngine::Keyboard::isDown(BadEngine::KeyCode::E))
    {
        rotation -= 0.05f;
    }
    if(BadEngine::Keyboard::isDown(BadEngine::KeyCode::Space))
    {
        rotation = 0;
    }
    m_Camera.setPosition(targetPosition);
    m_Camera.setZoomFactor(zoomFactor);
    m_Camera.setRotation(rotation);
}

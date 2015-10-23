#include <iostream>
#include <glm/glm.hpp>

#include <BadEngine/ImageLoader.h>
#include <BadEngine/Color.h>
#include <BadEngine/Keyboard.h>
#include <BadEngine/MathHelper.h>
#include <BadEngine/GLTexture.h>
#include <BadEngine/Camera2D.h>

#include "MainGame.h"
#include <BadEngine/ResourceManager.h>

MainGame::MainGame() : Game(1024, 768, 0, "GameEngine"),
    m_SpriteBatch(&m_Camera)
{
    setBackgroundColor(BadEngine::Color(0, 45, 75, 0));
    printf(" *** OpenGL version: %s *** \n You need at least version %5.2f to run the game. \n", 
           reinterpret_cast<const char*>(glGetString(GL_VERSION)), m_OpenGLVersion);
    m_Camera.setZoomFactor(2.0f);
}

MainGame::~MainGame()
{
}

void MainGame::draw()
{
    Game::draw();

    m_SpriteBatch.begin();

    BadEngine::Rectangle rectangle(glm::vec2(15, 15), 500, 500);
    BadEngine::Rectangle uvRectangle(glm::vec2(0, 0), 1, 1);

    for(auto i = 0; i < 1500; i++)
    {
        rectangle.setHeight((1520 - i) * 0.5f);
        rectangle.setWidth((1520 - i) * 0.5f);
        m_SpriteBatch.draw(m_ResourceManager.getTexture("Textures/PNG/CharacterRight_Walk1.png"),
                           rectangle, uvRectangle, BadEngine::Color::White);
    }
    m_SpriteBatch.end();
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

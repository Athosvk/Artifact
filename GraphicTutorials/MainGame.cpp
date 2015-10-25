#include <iostream>
#include <glm/glm.hpp>

#include <BadEngine/ImageLoader.h>
#include <BadEngine/Color.h>
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
        rectangle.setPosition(rectangle.getPosition() + glm::vec2(0, 1));
        rectangle.setHeight(100 - i * 0.07f);
        rectangle.setWidth(100 - i * 0.07f);
        static auto texture = m_ResourceManager.getTexture("Textures/PNG/CharacterRight_Walk1.png");
        m_SpriteBatch.draw(texture, rectangle, uvRectangle, BadEngine::Color::White);
    }
    m_SpriteBatch.end();
}

void MainGame::update()
{
    Game::update();

    static auto counter = 0;
    if(counter++ % 100 == 0)
    {
        std::cout << "FPS: " << 1 / m_GameTime.getAverageDeltaTime() << std::endl;
    }

    auto targetPosition = m_Camera.getPosition();
    auto zoomFactor = m_Camera.getZoomFactor();
    auto rotation = m_Camera.getRotation();
  
    m_Camera.setPosition(targetPosition);
    m_Camera.setZoomFactor(zoomFactor);
    m_Camera.setRotation(rotation);
}

#include <iostream>
#include <glm/glm.hpp>

#include <BadEngine/ImageLoader.h>
#include <BadEngine/Color.h>
#include <BadEngine/GLTexture.h>
#include <BadEngine/Camera2D.h>
#include <BadEngine/ResourceManager.h>

#include "MainGame.h"

MainGame::MainGame() : Game(1024, 768, 0, "GameEngine"),
    m_SpriteBatch(&m_Camera)
{
    setBackgroundColor(BadEngine::Color(0, 45, 75, 0));
    printf(" *** OpenGL version: %s *** \n You need at least version %5.2f to run the game. \n", 
           reinterpret_cast<const char*>(glGetString(GL_VERSION)), m_OpenGLVersion);
    m_Camera.setZoomFactor(1.0f);
}

MainGame::~MainGame()
{
}

void MainGame::draw()
{
    Game::draw();
    m_SpriteBatch.begin();

    BadEngine::Rectangle rectangle(glm::vec2(15, 15), 100, 100);
    BadEngine::Rectangle uvRectangle(glm::vec2(0, 0), 1, 1);

    static auto texture = m_ResourceManager.getTexture("Textures/PNG/CharacterRight_Walk1.png");
    m_SpriteBatch.draw(texture, rectangle, uvRectangle, BadEngine::Color::White);
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
}


void MainGame::fixedUpdate()
{
}

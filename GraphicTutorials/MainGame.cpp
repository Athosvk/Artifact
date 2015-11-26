#include <iostream>

#include "MainGame.h"

MainGame::MainGame() : Game(1024, 768, 0, "GameEngine"),
    m_SpriteBatch(&m_Camera),
    m_Player(m_ResourceManager),
    m_PlayerWeapon(m_Mouse, m_ResourceManager, m_Player.getTransform())
{
    setBackgroundColor(BadEngine::Color(0, 45, 75, 0));
    printf(" *** OpenGL version: %s *** \n You need at least version %5.2f to run the game. \n", 
           reinterpret_cast<const char*>(glGetString(GL_VERSION)), m_OpenGLVersion);
}

MainGame::~MainGame()
{
}

void MainGame::draw()
{
    Game::draw();
    m_SpriteBatch.begin();
    m_Player.draw(m_SpriteBatch);
    m_PlayerWeapon.draw(m_SpriteBatch);
    m_SpriteBatch.end();
}

void MainGame::update()
{
    Game::update();
    
    m_Player.update();
    m_PlayerWeapon.update();

    static auto counter = 0;
    if(counter++ % 100 == 0)
    {
        std::cout << "FPS: " << 1 / m_GameTime.getAverageDeltaTime() << std::endl;
    }
}

void MainGame::fixedUpdate()
{
    m_Player.fixedUpdate();
    m_PlayerWeapon.fixedUpdate();
}

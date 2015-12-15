#include <iostream>

#include "MainGame.h"

MainGame::MainGame() : Game(800, 600, 0, "GameEngine"),
    m_SpriteBatch(&m_Camera),
    m_Player(m_ResourceManager),
    m_PlayerWeapon(m_Mouse, m_Player.getTransform(), m_BulletPool, m_ResourceManager.getTexture("Textures/PNG/Pistol.png")),
    m_BulletPool(Bullet(m_ResourceManager.getTexture("Textures/PNG/Bullet.png"), glm::vec2(0, 0)), 1)
{
    setBackgroundColor(BadEngine::Color(0, 45, 75, 0));
    printf(" *** OpenGL version: %s *** \n You need at least version %5.2f to run the game. \n", 
           reinterpret_cast<const char*>(glGetString(GL_VERSION)), m_OpenGLVersion);
    m_Camera.setZoomFactor(2.0f);
    m_PlayerWeapon.setParent(&m_Player.getTransform());
}

MainGame::~MainGame()
{
}

void MainGame::draw()
{
    Game::draw();
    m_SpriteBatch.begin();
    for(auto& bullet : m_BulletPool)
    {
        if(bullet->isActive())
        {
            bullet->draw(m_SpriteBatch);
        }
    }
    m_Player.draw(m_SpriteBatch);
    m_PlayerWeapon.draw(m_SpriteBatch);
    m_SpriteBatch.end();
}

void MainGame::update()
{
    Game::update();
    
    m_Player.update();
    m_PlayerWeapon.update(m_GameTime);
    for(auto& bullet : m_BulletPool)
    {
        if(bullet->isActive())
        {
            bullet->update(m_GameTime);
        }
    }

    static auto counter = 0;
    if(counter++ % 100 == 0)
    {
        std::cout << "FPS: " << 1 / m_GameTime.getAverageDeltaTime() << std::endl;
    }
}

void MainGame::fixedUpdate()
{
    m_Player.fixedUpdate();
    for(auto& bullet : m_BulletPool)
    {
        if(bullet->isActive())
        {
            bullet->fixedUpdate();
        }
    }
}

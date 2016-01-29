#include <GL/glew.h>
#include "MathHelper.h"

#include "Game.h"

namespace BadEngine
{
    const double Game::FixedUpdateInterval = 0.008;
    const double Game::SpiralOfDeathThreshold = 0.075;

    Game::Game(int a_ScreenWidth, int a_ScreenHeight, Uint32 a_WindowFlags, std::string a_WindowName)
        : m_Window(a_ScreenWidth, a_ScreenHeight, a_WindowFlags, a_WindowName),
        m_Camera(m_Window),
        m_Mouse(m_Camera)
    {
    }

    void Game::setBackgroundColor(Color a_Color) const
    {
        glClearColor(a_Color.r / 255.0f, a_Color.g / 255.0f, a_Color.b / 255.0f, a_Color.a / 255.0f);
    }

    void Game::run()
    {
        startGameLoop();
    }

    void Game::startGameLoop()
    {
        while(m_CurrentGameState == GameState::Play)
        {
            m_Window.clear();
            update();
            processEvents();
            processFixedUpdates();
            m_Window.renderCurrentFrame();
        }
    }

    void Game::update()
    {
        m_CurrentWorld->update();
        m_Camera.update();
        m_Keyboard.update();
        m_Mouse.update();
        m_GameTime.update();
    }

    void Game::processFixedUpdates()
    {
        m_FixedUpdateTimer += m_GameTime.getDeltaTime();

        m_FixedUpdateTimer = MathHelper::min(SpiralOfDeathThreshold, m_FixedUpdateTimer);
        while(m_FixedUpdateTimer >= FixedUpdateInterval)
        {
            m_FixedUpdateTimer -= FixedUpdateInterval;
            fixedUpdate();
        }
    }

    void Game::fixedUpdate()
    {
        m_CurrentWorld->fixedUpdate();
    }

    void Game::processEvents()
    {
        SDL_Event evnt;
        while(SDL_PollEvent(&evnt) == 1)
        {
            switch(evnt.type)
            {
            case SDL_QUIT:
                m_CurrentGameState = GameState::Exit;
                break;
            case SDL_KEYDOWN:
            case SDL_KEYUP:
                m_Keyboard.process(evnt.key);
                break;
            case SDL_MOUSEBUTTONUP:
            case SDL_MOUSEBUTTONDOWN:
                m_Mouse.process(evnt.button);
            case SDL_MOUSEMOTION:
                m_Mouse.process(evnt.motion);
            case SDL_MOUSEWHEEL:
                m_Mouse.process(evnt.wheel);
            }
        }
    }
}


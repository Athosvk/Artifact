#include <GL/glew.h>
#include <iostream>

#include "MathHelper.h"

#include "Game.h"

namespace BadEngine
{
    const double Game::FixedUpdateInterval = 0.008;
    const double Game::SpiralOfDeathThreshold = 0.075;

    Game::Game(int a_ScreenWidth, int a_ScreenHeight, Uint32 a_WindowFlags, std::string a_WindowName)
        : m_Window(a_ScreenWidth, a_ScreenHeight, a_WindowFlags, a_WindowName)
    {
    }

    void Game::setBackgroundColor(Color a_Color) const
    {
        //Move to window
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
            processEvents();
            update();
            processFixedUpdates();
            m_Window.renderCurrentFrame();
        }
    }

    void Game::update()
    {
        m_CurrentWorld->update();
        m_GameTime.update();
        static int counter = 0;
        if(counter++ % 15 == 0)
        {
            std::cout << "FPS: " << 1 / m_GameTime.getAverageDeltaTime() << "\n";
        }
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
        SDL_Event sdlEvent;
        std::vector<SDL_Event> unhandledEvents;
        while(SDL_PollEvent(&sdlEvent) == 1)
        {
            switch(sdlEvent.type)
            {
            case SDL_QUIT:
                m_CurrentGameState = GameState::Exit;
                break;
            default:
                unhandledEvents.push_back(sdlEvent);
            }
        }
        m_CurrentWorld->processEvents(unhandledEvents);
    }
}


#include <iostream>

#include "Game.h"
#include "ErrorHandler.h"

namespace BadEngine
{
    Game::Game(int a_ScreenWidth, int a_ScreenHeight, Uint32 a_WindowFlags, std::string a_WindowName)    
    {
        initSDL();
        m_Window = new Window(a_ScreenWidth, a_ScreenHeight, a_WindowFlags, a_WindowName);
        m_Camera = new Camera2D(m_Window);
        initGL();
        SDL_GL_SetSwapInterval(1);
    }

    Game::~Game()
    {
    }

    void Game::setBackgroundColor(Color a_Color) const
    {
        glClearColor(a_Color.r / 255.0f, a_Color.g / 255.0f, a_Color.b / 255.0f, a_Color.a / 255.0f);
    }

    void Game::initSDL() const
    {
        SDL_Init(SDL_INIT_EVERYTHING);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    }

    void Game::initGL() const
    {
        auto initCode = glewInit();
        if(initCode != GLEW_OK)
        {
            throwFatalError("Could not init glew, error: " + std::string(reinterpret_cast<const char*>(glewGetErrorString(initCode))));
        }
    }

    void Game::draw()
    {

    }

    void Game::run()
    {
        startGameLoop();
    }

    void Game::startGameLoop()
    {
        while(m_CurrentGameState == GameState::Play)
        {
            m_Window->clear();
            processEvents();
            update();
            draw();
            m_Window->renderCurrentFrame();
        }
    }

    void Game::update()
    {
        m_Camera->update();
        m_Keyboard.update();
        m_GameTime.update();
    }

    void Game::processFixedUpdates()
    {
        m_FixedUpdateTimer += m_GameTime.getDeltaTime();
        while(m_FixedUpdateTimer >= m_FixedUpdateInterval)
        {
            m_FixedUpdateInterval -= m_FixedUpdateInterval;
            fixedUpdate();
        }
    }

    void Game::fixedUpdate()
    {

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
            }
        }
    }
}


#pragma once
#include <string>

#include "Window.h"
#include "GameTime.h"
#include "Color.h"
#include "Keyboard.h"
#include "Camera2D.h"

namespace BadEngine
{
    enum class GameState
    {
        Play, Exit
    };

    class Game
    {
    protected:
        const float m_OpenGLVersion = 3.00f;

        Window m_Window;
        GameState m_CurrentGameState = GameState::Play;
        GameTime m_GameTime = GameTime();
        Keyboard m_Keyboard = Keyboard();
        Camera2D m_Camera;
        double m_FixedUpdateInterval = 0.15;
        
    private:
        double m_FixedUpdateTimer = 0.0;

    public:
        virtual ~Game();
        void run();
        void setBackgroundColor(Color a_Color);

    protected:
        Game(int a_ScreenWidth, int a_ScreenHeight, unsigned int a_WindowFlags, std::string a_WindowName);
        virtual void draw();
        virtual void update();
        virtual void fixedUpdate();

    private:
        void initSDL();
        void initGL();
        void startGameLoop();
        void processFixedUpdates();
        void processEvents();
    };
}

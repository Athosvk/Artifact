#pragma once
#include "Rendering/Window.h"
#include "GameTime.h"
#include "Color.h"
#include "Input/Keyboard.h"
#include "Rendering/Camera2D.h"
#include "IO/ResourceManager.h"
#include "Input/Mouse.h"
#include "Core/World.h"

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
        GameTime m_GameTime;
        Keyboard m_Keyboard;
        Camera2D m_Camera;
        Mouse m_Mouse;
        std::unique_ptr<World> m_CurrentWorld;
        double m_FixedUpdateInterval = 0.030;
        
    private:
        double m_FixedUpdateTimer = 0.0;

    protected:
        Game(int a_ScreenWidth, int a_ScreenHeight, unsigned int a_WindowFlags, std::string a_WindowName);

    public:
        virtual ~Game() = default;

        void run();
        void setBackgroundColor(Color a_Color) const;

    protected:
        void update();
        void fixedUpdate();

        template<typename T>
        void loadWorld()
        {
            m_CurrentWorld = std::make_unique<T>(m_Window);
        }

    private:
        void startGameLoop();
        void processFixedUpdates();
        void processEvents();
    };
}
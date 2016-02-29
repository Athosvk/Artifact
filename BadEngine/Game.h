#pragma once
#include "Rendering/Window.h"
#include "GameTime.h"
#include "Color.h"
#include "IO/ResourceManager.h"
#include "Core/World.h"

namespace BadEngine
{
    enum class GameState
    {
        Play, Exit
    };

    class Game
    {
    public:
        static const double FixedUpdateInterval;

    protected:
        const float m_OpenGLVersion = 3.00f;
        static const double SpiralOfDeathThreshold;

        Window m_Window;
        GameState m_CurrentGameState = GameState::Play;
        GameTime m_GameTime;
        std::unique_ptr<World> m_CurrentWorld;
        std::unique_ptr<World> m_StagingWorld;
        
    private:
        double m_FixedUpdateTimer = 0.0;

    protected:
        Game(int a_ScreenWidth, int a_ScreenHeight, unsigned int a_WindowFlags, std::string a_WindowName);
    public:
        virtual ~Game() = default;

        void run();
        void setBackgroundColor(Color a_Color) const;

        template<typename T>
        void loadWorld()
        {
            if(m_CurrentWorld == nullptr)
            {
                m_CurrentWorld = std::make_unique<T>(m_GameTime, this);
            }
            else
            {
                m_StagingWorld = std::make_unique<T>(m_GameTime, this);
            }
        }

    protected:
        void update();
        void fixedUpdate();

    private:
        void startGameLoop();
        void processFixedUpdates();
        void processEvents();
        void switchWorld();
    };
}
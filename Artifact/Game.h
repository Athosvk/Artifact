#pragma once
#include "Rendering/Window.h"
#include "GameTime.h"
#include "Color.h"
#include "IO/ResourceManager.h"
#include "Core/World.h"

namespace Artifact
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
        std::unique_ptr<World> m_CurrentWorld = nullptr;
        std::unique_ptr<World> m_StagingWorld = nullptr;
        
    private:
        double m_FixedUpdateTimer = 0.0;

    protected:
        Game(int a_ScreenWidth, int a_ScreenHeight, unsigned int a_WindowFlags, const std::string& a_WindowName);
    public:
        virtual ~Game() = default;

        void run();

        template<typename T, typename ...TArguments>
        void loadWorld(TArguments&&... a_Arguments)
        {
            if(m_CurrentWorld == nullptr)
            {
                m_CurrentWorld = std::make_unique<T>(m_GameTime, this, std::forward<TArguments>(a_Arguments)...);
                m_CurrentWorld->awake();
            }
            else
            {
                m_StagingWorld = std::make_unique<T>(m_GameTime, this, std::forward<TArguments>(a_Arguments)...);
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
#pragma once
#include "Rendering/Window.h"
#include "GameTime.h"
#include "Color.h"
#include "IO/ResourceManager.h"
#include "Core/World.h"

namespace Artifact
{	
	/// <summary>
	/// Represents a gamestate, either being the active or the exiting stage
	/// </summary>
	enum class EGameState
    {		
		/// <summary>The playing state</summary>
		Play,		
		/// <summary>The quitting/exiting state</summary>
		Exit
    };
	
	/// <summary>
	/// The game that contains the necessary systems
	/// </summary>
	class Game
    {
    public:
		/// <summary>
		/// The game that contains the necessary systems
		/// </summary>
        static const double FixedUpdateInterval;

    protected:		
		/// <summary>The OpenGL version used by the game</summary>
		const float m_OpenGLVersion = 3.00f;
		/// <summary>
		/// The game that contains the necessary systems
		/// </summary>
		static const double SpiralOfDeathThreshold;
		
		/// <summary>The window that the game is displayed in</summary>
		Window m_Window;		
		/// <summary>The current game state</summary>
		EGameState m_CurrentGameState = EGameState::Play;		
		/// <summary>The game time</summary>
		GameTime m_GameTime;		
		/// <summary>The game world that is currently active</summary>
		std::unique_ptr<World> m_CurrentWorld = nullptr;		
		/// <summary>The game world pending to become the current world</summary>
		std::unique_ptr<World> m_StagingWorld = nullptr;

	private:
		/// <summary>The fixed update timer</summary>
		double m_FixedUpdateTimer = 0.0;

    protected:
		/// <summary>Initializes a new instance of the <see cref="Game"/> class.</summary>
		/// <param name="a_ScreenWidth">The width of the game screen</param>
		/// <param name="a_ScreenHeight">The height of the game screen</param>
		/// <param name="a_WindowFlags">The window flags</param>
		/// <param name="a_WindowName">The name of the game window</param>
		Game(int a_ScreenWidth, int a_ScreenHeight, unsigned int a_WindowFlags, const std::string& a_WindowName);
    public:		
		/// <summary>Finalizes an instance of the <see cref="Game"/> class.</summary>
		virtual ~Game() = default;
		
		/// <summary>Starts to run the game</summary>
		void run();

		/// <summary>Creates and loads a game world of the specified type</summary>
		/// <param name="...a_Arguments">The arguments for constructing the world instance</param>
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
		/// <summary>Updates the world</summary>
		void update();
		
		/// <summary>Runs the fixed update, for frame independent logic</summary>
		void fixedUpdate();

    private:		
		/// <summary>Starts the game loop</summary>
		void startGameLoop();
		
		/// <summary>Processes the fixed updates, so that fixed updates can be submitted</summary>
		void processFixedUpdates();
		
		/// <summary>Processes the events that were submitted</summary>
		void processEvents();
		
		/// <summary>Switches from the current world to the staging world</summary>
		void switchWorld();
    };
}
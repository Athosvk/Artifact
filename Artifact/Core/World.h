#pragma once
#include <memory>
#include <vector>
#include <SDL/SDL.h>

#include "EntitySystem.h"
#include "MessagingSystem.h"
#include "System.h"
#include "../GameTime.h"

namespace Artifact
{
    class System;
    class Message;
    class GameTime;
    class Game;
    	
	/// <summary>
	/// Sent every frame so that systems can execute the logic that needs to be executed on a per frame basis
	/// </summary>
	/// <seealso cref="Message" />
	class UpdateMessage : public Message
    {		
		/// <summary>The game time as presented at the start of this frame</summary>
		const GameTime& m_GameTime;
        
    public:		
		/// <summary>Initializes a new instance of the <see cref="UpdateMessage"/> class.</summary>
		/// <param name="a_GameTime">The information about the time passed in the game</param>
		explicit UpdateMessage(const GameTime& a_GameTime);
		
		/// <summary>Gets the game time containing the time information of the start of the frame</summary>
		/// <returns>The information about the elapsed time</returns>
		const GameTime& getGameTime() const;
    };
	
	/// <summary>
	/// A message that is sent a fixed amount of times per second (at possibly varying intervals) so actions
	/// can be executed frame-independently
	/// </summary>
	/// <seealso cref="Message" />
	class FixedUpdateMessage : public Message
    {
    };
	
	/// <summary>
	/// A message that is sent every frame to allow the systems for processing outstanding events 
	/// </summary>
	/// <seealso cref="Message" />
	class ProcessEventsMessage : public Message
    {		
		/// <summary>The events that have not been processed yet</summary>
		const std::vector<SDL_Event>& m_Events;

    public:		
		/// <summary>Initializes a new instance of the <see cref="ProcessEventsMessage"/> class.</summary>
		/// <param name="a_Events">The a_ events.</param>
		explicit ProcessEventsMessage(const std::vector<SDL_Event>& a_Events);
		
		/// <summary>Gets the events that were retrieved from the underlying event queue in this frame</summary>
		/// <returns>The events to process</returns>
		const std::vector<SDL_Event>& getEvents() const;
    };
	
	/// <summary>
	/// A message that is sent every fixed update to allow the physics implementation to advance their simulation,
	/// assuming frame independent behaviour
	/// </summary>
	/// <seealso cref="Message" />
	class PhysicsUpdateMessage : public Message
    {
    };
	
	/// <summary>
	/// A message that is sent at the time of initialization of the world, so that systems can perform such initialization
	/// tasks
	/// </summary>
	/// <seealso cref="Message" />
	class AwakeMessage : public Message
    {
    };
	
	/// <summary>
	/// The world containing the entities and systems that are operating and that is being operated on
	/// </summary>
	class World
    {
    protected:
		/// <summary>The entity system linking the entities against their respective components</summary>
		EntitySystem m_EntitySystem;
		/// <summary>The messaging system used for communication the systems in the world</summary>
		MessagingSystem m_MessagingSystem;		
		/// <summary>The active game instance</summary>
		Game* m_CurrentGame;

    private:		
		/// <summary>The systems operating in the world</summary>
		std::vector<std::unique_ptr<System>> m_Systems;		
		/// <summary>The current game time</summary>
		GameTime& m_GameTime;

    public:		
		/// <summary>Initializes a new instance of the <see cref="World"/> class.</summary>
		/// <param name="a_GameTime">The time information of the game</param>
		/// <param name="a_CurrentGame">The currently active game</param>
		World(GameTime& a_GameTime, Game* a_CurrentGame);

		/// <summary>Finalizes an instance of the <see cref="World"/> class.</summary>
		virtual ~World() = default;
		
		/// <summary>Awakes the world, allowing it to initialize all the entities</summary>
		void awake();
		
		/// <summary>Allows the world to update the systems, in turn allowing them to update the state of the world</summary>
		void update();

		/// <summary>Executes the update that is assumed to be frame-independent </summary>
		void fixedUpdate();
		
		/// <summary>Allows the world to process events that were stored in the event queue</summary>
		/// <param name="a_Events">The events to process</param>
		void processEvents(std::vector<SDL_Event>& a_Events);
    protected:
		/// <summary>Creates and adds a system of the given type to operate in this world</summary>
		template<typename T>
        void addSystem()
        {
            auto newSystem = std::make_unique<T>(m_EntitySystem, m_MessagingSystem);
            newSystem->registerListeners();
            m_Systems.emplace_back(std::move(newSystem));
        }

		/// <summary>Constructs a message from the given arguments and broadcasts it using the messaging system</summary>
		/// <param name="...a_MessageArguments">The ...a_ message arguments.</param>
		template<typename TMessageType, typename... TArguments>
        void broadcast(TArguments&&... a_MessageArguments)
        {
            m_MessagingSystem.broadcast<TMessageType, TArguments...>(std::forward<TArguments>(a_MessageArguments)...);
        }

    private:		
		/// <summary>Adds the system that should be present for every game</summary>
		void addDefaultSystems();
    };
}


#pragma once
#include <vector>

namespace Artifact
{
    class EntitySystem;
	class MessagingSystem;

	/// <summary>
	/// Represents a system that executes logic on or based on the data stored in components of the component 
	/// types it is interested in
	/// </summary>
	class System
    {
    protected:
		/// <summary>The entity system that contains the entities and components that this system is operating on</summary>
		EntitySystem& m_EntitySystem;
		/// <summary>The messaging system this system is using to communicate with the other systems in the world</summary>
		MessagingSystem& m_MessagingSystem;

    public:		
		/// <summary>Initializes a new instance of the <see cref="System"/> class.</summary>
		/// <param name="a_EntitySystem">The entity sytem to operate on</param>
		/// <param name="a_MessagingSystem">The messaging system</param>
		System(EntitySystem& a_EntitySystem, MessagingSystem& a_MessagingSystem);

		/// <summary>Finalizes an instance of the <see cref="System"/> class.</summary>
		virtual ~System() = default;

		/// <summary>Allows the system for registering itself to the messages it wants to listen to	</summary>
		virtual void registerListeners() = 0;
    };
}